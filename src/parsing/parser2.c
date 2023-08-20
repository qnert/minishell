/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:27:51 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/20 18:58:57 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_outfile_vars(t_shell *sh, t_lexer *curr, int pipes, int check)
{
	sh->outfiles->file_name = ft_strdup(curr->next->str);
	if (check == 1)
		sh->outfiles->fd = outfile_check_app(sh->outfiles->file_name);
	else
		sh->outfiles->fd = ft_outfile_check(sh->outfiles->file_name);
	sh->outfiles->delim = NULL;
	sh->outfiles->pos = pipes;
}

void	get_outfile(t_shell *sh)
{
	t_lexer	*curr;
	int		pipes;

	pipes = 0;
	curr = sh->token_list;
	while (curr)
	{
		if (curr->token == PIPE)
			pipes++;
		if (curr->token == GREAT_GREAT)
			get_outfile_append(sh);
		if (curr->token == GREAT)
		{
			if (sh->outfiles == NULL)
			{
				sh->outfiles = malloc(sizeof(t_files));
				set_outfile_vars(sh, curr, pipes, 0);
				sh->outfiles->next = NULL;
			}
			else
				lst_add_new_outfile(sh->outfiles, curr->next->str,
					curr->token, pipes);
		}
		curr = curr->next;
	}
}

void	get_outfile_append(t_shell *sh)
{
	t_lexer	*curr;
	int		pipes;

	pipes = 0;
	curr = sh->token_list;
	while (curr)
	{
		if (curr->token == PIPE)
			pipes++;
		if (curr->token == GREAT_GREAT)
		{
			if (sh->outfiles == NULL)
			{
				sh->outfiles = malloc(sizeof(t_files));
				set_outfile_vars(sh, curr, pipes, 1);
				sh->outfiles->next = NULL;
			}
			else
				lst_add_new_outfile(sh->outfiles, curr->next->str,
					curr->token, pipes);
		}
		curr = curr->next;
	}
}
