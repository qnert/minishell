/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:36:27 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/18 00:30:59 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_files	*get_right_file(t_shell *sh, t_files *file)
{
	t_files	*curr;

	curr = file;
	if (!curr)
		return (NULL);
	if (sh->pipes > 0 && (!curr->next || curr->pos != sh->index))
		return (curr);
	while (curr && curr->next)
	{
		if (curr->fd == -1)
			return (curr);
		if (curr->pos != curr->next->pos)
			return (curr);
		curr = curr->next;
	}
	return (curr);
}
