/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:36:27 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/20 18:32:09 by njantsch         ###   ########.fr       */
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

void	lst_add_new_here_doc(t_files *lst, t_lexer *lex, int pipe)
{
	t_files	*curr;
	t_files	*new_node;

	curr = lst;
	new_node = malloc(sizeof(t_files));
	while (curr->next)
		curr = curr->next;
	if (lex->next->token == SINGLE || lex->next->token == DOUBLE
		|| (lex->next->next && lex->next->next->token == SINGLE
			&& ft_strlen(lex->next->next->str) == 0)
		|| (lex->next->next && lex->next->next->token == DOUBLE
			&& ft_strlen(lex->next->next->str) == 0))
		new_node->file_name
			= right_here_doc_name(lst, "here_docc", 1);
	else
		new_node->file_name
			= right_here_doc_name(lst, "here_doc", 1);
	set_new_node_hd(curr, lex, new_node, pipe);
}

void	set_new_node_hd(t_files *curr, t_lexer *lex, t_files *new, int pipe)
{
	if ((lex->next->token == SINGLE
			&& ft_strlen(lex->next->str) == 0 && lex->next->next)
		|| (lex->next->token == DOUBLE
			&& ft_strlen(lex->next->str) == 0 && lex->next->next))
		new->delim = ft_strdup(lex->next->next->str);
	else
		new->delim = ft_strdup(lex->next->str);
	new->fd = ft_outfile_check(new->file_name);
	new->pos = pipe;
	new->next = NULL;
	curr->next = new;
}
