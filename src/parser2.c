/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:27:51 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/22 17:46:03 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (curr->token == GREAT)
		{
			if (sh->outfiles == NULL)
			{
				sh->outfiles = malloc(sizeof(t_files));
				sh->outfiles->file_name = ft_strdup(curr->next->str);
				sh->outfiles->delim = NULL;
				sh->outfiles->fd = ft_outfile_check(sh->outfiles->file_name);
				sh->outfiles->pos = pipes;
				sh->outfiles->next = NULL;
			}
			else
				lst_add_new_file(sh->outfiles, curr->next->str, NULL, pipes);
		}
		curr = curr->next;
	}
}
