/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:19:39 by skunert           #+#    #+#             */
/*   Updated: 2023/08/16 12:50:14 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	lst_add_new(t_lexer *lst, char *str, int token)
{
	t_lexer	*curr;
	t_lexer	*new_node;

	curr = lst;
	new_node = malloc(sizeof(t_lexer));
	if (new_node == NULL)
		return (-1);
	new_node->str = str;
	new_node->token = token;
	new_node->f_space = 0;
	new_node->b_space = 0;
	new_node->next = NULL;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
	return (1);
}

void	lst_add_new_infile(t_files *lst, char *str, char *delim, int pipe)
{
	t_files	*curr;
	t_files	*new_node;

	curr = lst;
	new_node = malloc(sizeof(t_files));
	while (curr->next)
		curr = curr->next;
	if (str == NULL)
		new_node->file_name = ft_strdup("here_doc");
	else
		new_node->file_name = ft_strdup(str);
	if (delim != NULL)
		new_node->delim = ft_strdup(delim);
	else
		new_node->delim = NULL;
	if (new_node->delim != NULL)
		new_node->fd = ft_outfile_check(new_node->file_name);
	else
		new_node->fd = ft_infile_check(new_node->file_name);
	new_node->pos = pipe;
	new_node->next = NULL;
	curr->next = new_node;
}

void	lst_add_new_outfile(t_files *lst, char *str, int token, int pipe)
{
	t_files	*curr;
	t_files	*new_node;

	curr = lst;
	new_node = malloc(sizeof(t_files));
	while (curr->next)
		curr = curr->next;
	new_node->file_name = ft_strdup(str);
	new_node->delim = NULL;
	if (token == GREAT)
		new_node->fd = ft_outfile_check(new_node->file_name);
	else if (token == GREAT_GREAT)
		new_node->fd = outfile_check_app(new_node->file_name);
	new_node->pos = pipe;
	new_node->next = NULL;
	curr->next = new_node;
}

void	free_lst_lexer(t_lexer *lst)
{
	t_lexer	*curr;
	t_lexer	*tmp;

	curr = lst;
	while (curr != NULL)
	{
		free(curr->str);
		curr->str = NULL;
		curr = curr->next;
	}
	curr = lst;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

void	free_lst_files(t_files *lst)
{
	t_files	*curr;
	t_files	*tmp;

	curr = lst;
	while (curr != NULL)
	{
		if (curr->file_name)
			free(curr->file_name);
		if (curr->delim != NULL)
			free(curr->delim);
		if (curr->fd != -1)
			close(curr->fd);
		curr = curr->next;
	}
	curr = lst;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}
