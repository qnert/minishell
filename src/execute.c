/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:41:03 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/02 15:28:19 by njantsch         ###   ########.fr       */
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

void	execute_cmd(t_shell *sh, t_files *infile)
{
	char	**tmp;

	tmp = NULL;
	if (check_built_in_child(sh->cmd_table[0]) == true)
	{
		handle_built_in(sh, sh->cmd_table[0]);
		terminate_struct(sh);
		free_arr(tmp);
		free_arr(sh->envp);
		free(sh);
		exit(EXIT_SUCCESS);
	}
	if (infile == NULL || infile->fd > 0)
	{
		tmp = ft_split(sh->cmd_table[0], 1);
		execve(sh->path_to_file_table[0], tmp, sh->envp);
	}
	printf("minishell: %s: command not found\n", tmp[0]);
	terminate_struct(sh);
	free_arr(tmp);
	free_arr(sh->envp);
	free(sh);
	exit(127);
}

void	execute_no_pipes(t_shell *sh, t_files *infile, t_files *outfile)
{
	pid_t	pid2;

	outfile = ft_lstlast_files(sh->outfiles);
	infile = ft_lstlast_files(sh->infiles);
	if (check_built_in_main(sh->cmd_table[0]) == true)
		return (handle_built_in(sh, sh->cmd_table[0]));
	pid2 = fork();
	if (pid2 == 0)
	{
		which_dup(infile, outfile);
		execute_cmd(sh, infile);
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
