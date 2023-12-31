/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:55:39 by skunert           #+#    #+#             */
/*   Updated: 2023/08/19 15:56:52 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	check_null(char *str, int i)
{
	if (str[i] == '\0')
		return (true);
	return (false);
}

void	check_pipe(t_shell *sh, char *str, int i)
{
	if (str[i] == '|')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup("|");
			sh->token_list->token = PIPE;
			sh->token_list->f_space = 0;
			sh->token_list->b_space = 0;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, ft_strdup("|"), PIPE);
	}
}

void	check_redirect_plus(t_shell *sh, char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup("<<");
			sh->token_list->token = LESS_LESS;
			sh->token_list->f_space = 0;
			sh->token_list->b_space = 0;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, ft_strdup("<<"), LESS_LESS);
	}
	check_redirect_plus_helper(sh, str, i);
}

void	check_redirect(t_shell *sh, char *str, int i)
{
	if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup("<");
			sh->token_list->token = LESS;
			sh->token_list->f_space = 0;
			sh->token_list->b_space = 0;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, ft_strdup("<"), LESS);
	}
	check_redirect_helper(sh, str, i);
	check_redirect_plus(sh, str, i);
}

bool	lexer(t_shell *sh, char *str)
{
	int	i;

	i = 0;
	while (1)
	{
		if (check_null(str, i) == true)
			break ;
		check_pipe(sh, str, i);
		check_redirect(sh, str, i);
		i = check_words(sh, str, i);
		i = check_single_quotes(sh, str, i);
		if (i == -1)
			return (false);
		i = check_double_quotes(sh, str, i);
		if (i == -1)
			return (false);
		i++;
	}
	return (true);
}
