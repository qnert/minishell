/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:41:03 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/25 19:01:39 by njantsch         ###   ########.fr       */
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
		tmp = ft_split(sh->cmd_table[0], ' ');
		execve(sh->path_to_file_table[0], tmp, sh->envp);
	}
	perror("execve");
	terminate_struct(sh);
	free_arr(tmp);
	free_arr(sh->envp);
	free(sh);
	exit(1);
}

void	execute_no_pipes(t_shell *sh, t_files *infile, t_files *outfile)
{
	int		i;
	pid_t	pid2;

	i = 0;
	outfile = ft_lstlast_files(sh->outfiles);
	infile = ft_lstlast_files(sh->infiles);
	while (sh->cmd_table[i])
	{
		if (check_built_in_main(sh->cmd_table[i]) == true)
			return (handle_built_in(sh, sh->cmd_table[i]));
		pid2 = fork();
		if (pid2 == 0)
		{
			which_dup(infile, outfile);
			execute_cmd(sh, infile);
		}
		waitpid(pid2, &sh->status, 0);
		i++;
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
	{
		execute_no_pipes(sh, infile, outfile);
		check_exit(sh);
	}
}
