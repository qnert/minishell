/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:10:38 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/22 12:28:00 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_list(t_shell *sh)
{
	t_lexer	*curr;

	curr = sh->token_list;
	while (curr)
	{
		if (sh->token_list->token == 1)
			return (false);
		if (curr->next == NULL && curr->token > 0 && curr->token < 6)
			return (false);
		if (curr->next && curr->token > 0 && curr->token < 6
			&& curr->token == curr->next->token)
			return (false);
		curr = curr->next;
	}
	return (true);
}

void	get_infile(t_shell *sh)
{
	int		pipe;
	t_lexer	*curr;

	pipe = 0;
	curr = sh->token_list;
	while (curr)
	{
		if (curr->token == PIPE)
			pipe++;
		if (curr->token == 4)
		{
			if (sh->infiles == NULL)
			{
				sh->infiles = malloc(sizeof(t_files));
				sh->infiles->file_name = ft_strdup(curr->next->str);
				sh->infiles->delim = NULL;
				sh->infiles->fd = ft_infile_check(sh->infiles->file_name);
				sh->infiles->pos = pipe;
				sh->infiles->next = NULL;
			}
			else
				lst_add_new_infile(sh->infiles, curr->next->str, NULL, pipe);
		}
		curr = curr->next;
	}
}

void	get_here_doc(t_shell *sh)
{
	int		pipe;
	t_lexer	*curr;

	pipe = 0;
	curr = sh->token_list;
	while (curr)
	{
		if (curr->token == PIPE)
			pipe++;
		if (curr->token == 5)
		{
			if (sh->infiles == NULL)
			{
				sh->infiles = malloc(sizeof(t_files));
				sh->infiles->file_name = ft_strdup("here_doc");
				sh->infiles->delim = ft_strdup(curr->next->str);
				sh->infiles->fd = ft_outfile_check(sh->infiles->file_name);
				sh->infiles->pos = pipe;
				sh->infiles->next = NULL;
			}
			else
				lst_add_new_infile(sh->infiles, NULL, curr->next->str, pipe);
		}
		curr = curr->next;
	}
}

bool	parser_main(t_shell *sh)
{
	if (sh->token_list == NULL)
		return (true);
	if (check_list(sh) == false)
		return (false);
	get_infile(sh);
	get_here_doc(sh);
	return (true);
}
