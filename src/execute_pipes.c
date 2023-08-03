/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:49:56 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/03 16:09:04 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	which_dup_pipes(t_shell *sh, t_files *in, t_files *out, int *fd)
{
	if (in && in->fd && sh->index == in->pos)
	{
		close(fd[0]);
		dup2(in->fd, STDIN_FILENO);
	}
	else
		close(fd[0]);
	if (out && out->fd && sh->index == out->pos)
	{
		close(fd[1]);
		dup2(out->fd, STDOUT_FILENO);
	}
	else if (sh->index != get_len_matrix(sh->cmd_table) - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
		close(fd[1]);
}

void	child_process_pipes(t_shell *sh, t_files *in, t_files *out)
{
	char	**tmp;

	tmp = NULL;
	if (check_built_in_child(sh->cmd_table[sh->index]) == true
	&& ((in == NULL || in->fd > 0) && (out == NULL || out->fd > 0)))
	{
		handle_built_in(sh, sh->cmd_table[sh->index]);
		exit_status(sh, tmp, 0);
	}
	if ((in == NULL || in->fd > 0) && (out == NULL || out->fd > 0))
	{
		tmp = ft_split(sh->cmd_table[sh->index], 1);
		execve(sh->path_to_file_table[sh->index], tmp, sh->envp);
		printf("%s\n", sh->path_to_file_table[sh->index]);
	}
	if (access(sh->path_to_file_table[sh->index], F_OK) == -1)
	{
		write(2, "minishell: command not found\n", 29);
		exit_status(sh, tmp, 127);
	}
	else if (access(sh->path_to_file_table[sh->index], X_OK) == -1
		&& access(sh->path_to_file_table[sh->index], F_OK) == 0)
	{
		write(2, "minishell: non executable\n", 26);
		exit_status(sh, tmp, 126);
	}
	perror("minishell");
	exit_status(sh, tmp, 1);
}

void	redirect_for_other_pipe(int	*fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

int	handle_child_pipes(t_shell *sh, t_files *in, t_files *out, int *fd)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
	{
		if (check_built_in_main(sh->cmd_table[sh->index]) == true)
			handle_built_in(sh, sh->cmd_table[sh->index]);
		which_dup_pipes(sh, in, out, fd);
		child_process_pipes(sh, in, out);
	}
	else
		redirect_for_other_pipe(fd);
	return (pid);
}

void	execute_pipes(t_shell *sh, t_files *in, t_files *out)
{
	int		fd[2];
	pid_t	pid;

	sh->index = 0;
	in = sh->infiles;
	out = sh->outfiles;
	sh->old_stdin = dup(STDIN_FILENO);
	while (sh->cmd_table[sh->index])
	{
		in = get_right_file(sh, in);
		out = get_right_file(sh, out);
		pid = handle_child_pipes(sh, in, out, fd);
		if (in && in->fd && in->pos == sh->index)
			in = in->next;
		if (out && out->fd && out->pos == sh->index)
			out = out->next;
		sh->index++;
	}
	waitpid(pid, &sh->status, 0);
	dup2(sh->old_stdin, STDIN_FILENO);
	close(sh->old_stdin);
}
