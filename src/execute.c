/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:41:03 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/14 11:47:00 by skunert          ###   ########.fr       */
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

void	execute_cmd(t_shell *sh, t_files *in, t_files *out)
{
	char	**tmp;
	DIR		*dir;

	tmp = NULL;
	if (check_built_in_child(sh->cmd_table[0]) == true
		&& ((in == NULL || in->fd > 0) && (out == NULL || out->fd > 0)))
	{
		handle_built_in(sh, sh->cmd_table[0]);
		exit_status(sh, tmp, 0);
	}
	if ((in == NULL || in->fd > 0) && (out == NULL || out->fd > 0))
	{
		tmp = ft_split(sh->cmd_table[0], 1);
		if (ft_strnstr(sh->cmd_table[0], "./", 2) == NULL)
			execve(sh->path_to_file_table[0], tmp, sh->envp);
	}
	dir = opendir(sh->path_to_file_table[0]);
	exit_error(sh, tmp, dir, 0);
}

void	execute_no_pipes(t_shell *sh, t_files *infile, t_files *outfile)
{
	pid_t	pid2;

	outfile = get_right_file(sh, sh->outfiles);
	infile = ft_lstlast_files(sh->infiles);
	if (check_built_in_main(sh->cmd_table[0]) == true)
		return (handle_built_in(sh, sh->cmd_table[0]));
	pid2 = fork();
	if (pid2 == 0)
	{
		if (outfile && outfile->fd == -1)
			exit_status(sh, NULL, 1);
		which_dup(infile, outfile);
		execute_cmd(sh, infile, outfile);
	}
	waitpid(pid2, &sh->status, 0);
}

void	execute_main(t_shell *sh)
{
	t_files	*infile;
	t_files	*outfile;

	outfile = NULL;
	infile = NULL;
	check_cmd(sh);
	if (sh->pipes == 0)
	{
		execute_no_pipes(sh, infile, outfile);
		check_exit(sh);
	}
	else
	{
		execute_pipes(sh, infile, outfile);
		check_exit(sh);
	}
}
