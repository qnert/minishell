/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:19:26 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/21 14:51:59 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_words(t_shell *sh, char *str, int i)
{
	int	start;

	start = i;
	if (is_whitespace(str[i]) == true)
		return (i);
	while (is_whitespace(str[i]) == false && str[i])
		i++;
	i--;
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

int	check_single_quotes(t_shell *sh, char *str, int i)
{
	int	start;

	start = i + 1;
	if (str[i] != '\'')
		return (i);
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\0')
		return (-1);
	if (sh->token_list == NULL)
	{
		sh->token_list = malloc(sizeof(t_lexer));
		sh->token_list->str = ft_substr(str, start, i - start);
		sh->token_list->token = SINGLE;
		sh->token_list->next = NULL;
	}
	else
		lst_add_new(sh->token_list, ft_substr(str, start, i - start), SINGLE);
	return (i);
}

int	check_double_quotes(t_shell *sh, char *str, int i)
{
	int	start;

	start = i + 1;
	if (str[i] != '\"')
		return (i);
	i++;
	while (str[i] && str[i] != '\"')
		i++;
	if (str[i] == '\0')
		return (-1);
	if (sh->token_list == NULL)
	{
		sh->token_list = malloc(sizeof(t_lexer));
		sh->token_list->str = ft_substr(str, start, i - start);
		sh->token_list->token = DOUBLE;
		sh->token_list->next = NULL;
	}
	else
		lst_add_new(sh->token_list, ft_substr(str, start, i - start), DOUBLE);
	return (i);
}

bool	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"')
		return (true);
	return (false);
}
