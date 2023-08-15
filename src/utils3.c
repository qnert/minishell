/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:49:35 by skunert           #+#    #+#             */
/*   Updated: 2023/08/15 12:19:58 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_len(t_lexer *files)
{
	int		i;
	t_lexer	*curr;

	i = 0;
	curr = files;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

bool	check_word_token(int token)
{
	if (token == 0)
		return (true);
	if (token == 6)
		return (true);
	if (token == 7)
		return (true);
	return (false);
}

t_files	*ft_lstlast_files(t_files *lst)
{
	t_files	*curr_pos;

	curr_pos = lst;
	while (curr_pos != NULL && curr_pos->next != NULL)
	{
		curr_pos = curr_pos->next;
	}
	return (curr_pos);
}

void	replace_split_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 1)
			str[i] = 32;
		i++;
	}
}

t_lexer	*get_right_start_point(t_shell *sh)
{
	t_lexer	*curr;
	t_lexer	*tmp;

	curr = sh->token_list;
	if (!sh->infiles || !sh->infiles->next || sh->pipes == 0)
		return (curr);
	if (sh->outfiles->pos == sh->outfiles->next->pos)
		return (curr);
	while (curr)
	{
		if (curr->token > 3 && curr->token < 6)
			tmp = curr;
		curr = curr->next;
	}
	curr = tmp;
	sh->pipes = 0;
	while (curr)
	{
		if (curr->token == PIPE)
			sh->pipes++;
		curr = curr->next;
	}
	return (tmp);
}
