/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:49:35 by skunert           #+#    #+#             */
/*   Updated: 2023/07/27 15:34:42 by skunert          ###   ########.fr       */
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

bool	ft_check_flag(char *str, int *i, int *check)
{
	int	tmp;

	tmp = 0;
	if (str[*i] != '-')
		return (false);
	while (str[*i] && str[*i] == '-')
	{
		(*i)++;
		while (str[*i] && str[*i] != 32)
		{
			if (str[*i] == 'n')
				(*i)++;
			else
			{
				*i = tmp;
				return (true);
			}
		}
		(*i)++;
		tmp = (*i);
	}
	(*check) = 1;
	printf("%s", &str[*i]);
	return (true);
}
