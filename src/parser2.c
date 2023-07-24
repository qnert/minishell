/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:27:51 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/24 17:10:39 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_outfile_vars(t_shell *sh, int pipes)
{
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
		if (curr->token == GREAT || curr->token == GREAT_GREAT)
		{
			if (sh->outfiles == NULL)
			{
				sh->outfiles = malloc(sizeof(t_files));
				sh->outfiles->file_name = ft_strdup(curr->next->str);
				sh->outfiles->fd = ft_outfile_check(sh->outfiles->file_name);
				set_outfile_vars(sh, pipes);
				sh->outfiles->next = NULL;
			}
			else
				lst_add_new_outfile(sh->outfiles, curr->next->str,
					curr->token, pipes);
		}
		curr = curr->next;
	}
}

void	expander(t_shell *sh)
{
	int		i;
	t_lexer	*curr;

	i = 0;
	curr = sh->token_list;
	while (curr)
	{
		if (ft_strchr(curr->str, '$') != 0)
			get_expand(sh, curr->str, curr);
		curr = curr->next;
	}
}

void	read_till_limiter(t_files *curr)
{
	char	*line;

	printf("Eingabe erreicht\n");
	printf("file descirptor: %d\n", curr->fd);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, curr->delim, ft_strlen(curr->delim)) != 0)
	{
		ft_putstr_fd(line, curr->fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	printf("read finished\n");
	printf("file descirptor: %d\n", curr->fd);
}

void	check_and_write_here_doc(t_files *infiles)
{
	t_files	*curr;

	curr = infiles;
	while (curr)
	{
		if (curr->delim != NULL)
			read_till_limiter(curr);
		curr = curr->next;
	}
}
