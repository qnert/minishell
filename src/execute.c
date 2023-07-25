/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:41:03 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/25 12:30:10 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	which_dup(t_files *infile, t_files *outfile)
{
	if (infile && infile->fd)
	{
		dup2(infile->fd, STDIN_FILENO);
	}
	if (outfile && outfile->fd)
	{
		dup2(outfile->fd, STDOUT_FILENO);
	}
}

void	execute_no_pipes(t_shell *sh, t_files *infile, t_files *outfile)
{
	int		i;
	pid_t	pid2;

	i = 0;
	outfile = sh->outfiles;
	infile = sh->infiles;
	while (sh->cmd_table[i] || infile || outfile)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			which_dup(infile, outfile);
			if (check_built_in(sh->cmd_table[i]) == true)
				handle_built_in(sh, sh->cmd_table[i]);
			if (infile == NULL || infile->fd > 0)
				execve(sh->path_to_file_table[i],
					ft_split(sh->cmd_table[i], ' '), sh->envp);
		}
		waitpid(pid2, &sh->status, 0);
		i++;
		if (infile)
			infile = infile->next;
		if (outfile)
			outfile = outfile->next;
	}
}

void	execute_main(t_shell *sh)
{
	t_files	*infile;
	t_files	*outfile;

	outfile = NULL;
	infile = NULL;
	check_cmd(sh);
	if (sh->pipes == 0)
		execute_no_pipes(sh, infile, outfile);
}
