/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:41:03 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/22 18:51:12 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (check_built_in_child(sh, sh->cmd_table[0]) == true
		&& ((in == NULL || in->fd > 0) && (out == NULL || out->fd > 0)))
	{
		handle_built_in(sh, sh->cmd_table[0]);
		exit_status(sh, tmp, 0);
	}
	if ((in == NULL || in->fd > 0) && (out == NULL || out->fd > 0))
	{
		tmp = ft_split(sh->cmd_table[0], 1);
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
	if (check_built_in_main(sh, sh->cmd_table[0]) == true)
		return (handle_built_in(sh, sh->cmd_table[0]));
	pid2 = fork();
	if (pid2 == 0)
	{
		if (outfile && outfile->fd == -1)
		{
			write(2, "minishell: no such file or directory\n", 38);
			exit_status(sh, NULL, 1);
		}
		which_dup(infile, outfile);
		execute_cmd(sh, infile, outfile);
	}
	waitpid(pid2, &sh->status, 0);
	sh->status = get_exit_code(sh);
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
		check_exit(sh);
		g_cntrlc = 1;
		execute_no_pipes(sh, infile, outfile);
	}
	else
	{
		check_exit(sh);
		g_cntrlc = 1;
		execute_pipes(sh, infile, outfile);
	}
}
