/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:19:26 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/20 18:30:14 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_words(t_shell *sh, char *str, int i)
{
	int	start;

	start = i;
	if (str[i] != '-' && ft_isalnum(str[i]) == 0)
		return (i);
	while ((str[i] == '-' || ft_isalpha(str[i]) == 1) && str[i])
		i++;
	if (sh->token_list == NULL)
	{
		sh->token_list = malloc(sizeof(t_lexer));
		sh->token_list->str = ft_substr(str, start, i - start + 1);
		sh->token_list->token = 0;
		sh->token_list->next = NULL;
	}
	else
		lst_add_new(sh->token_list, ft_substr(str, start, i - start + 1), 0);
	return (i);
}

bool	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}
