/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:49:35 by skunert           #+#    #+#             */
/*   Updated: 2023/07/29 13:48:00 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_len(t_files *files)
{
	int		i;
	t_files	*curr;

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
	if (!sh->infiles || !sh->infiles->next)
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
