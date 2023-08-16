/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:53:27 by skunert           #+#    #+#             */
/*   Updated: 2023/08/16 16:56:40 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_redirect_plus_helper(t_shell *sh, char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup(">>");
			sh->token_list->token = GREAT_GREAT;
			sh->token_list->f_space = 0;
			sh->token_list->b_space = 0;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, ft_strdup(">>"), GREAT_GREAT);
	}
}

void	check_redirect_helper(t_shell *sh, char *str, int i)
{
	if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup(">");
			sh->token_list->token = GREAT;
			sh->token_list->f_space = 0;
			sh->token_list->b_space = 0;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, ft_strdup(">"), GREAT);
	}
}
