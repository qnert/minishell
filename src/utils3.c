/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:49:35 by skunert           #+#    #+#             */
/*   Updated: 2023/07/25 16:57:55 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_len(t_files *files)
{
	int		i;
	t_files	*curr;

	if (files == NULL)
		i = 1;
	else
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
