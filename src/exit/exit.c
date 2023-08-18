/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:26:08 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/18 16:50:03 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

long long	ft_atoll(const char *str);

void	check_failing_exit(t_shell *sh, int i, int j)
{
	if (ft_strchr(&sh->cmd_table[i][j], 1) != 0
		&& !ft_isalpha(sh->cmd_table[i][j]))
	{
		write(2, " too many arguments\n", 20);
		terminate_struct(sh);
		free_arr(sh->envp);
		free(sh);
		exit (1);
	}
	if (ft_isalpha(sh->cmd_table[i][j]) || ft_atoll(&sh->cmd_table[i][j])
		>= 9223372036854775807 || (sh->cmd_table[i][j] == '+'
		&& sh->cmd_table[i][j + 1] == '+')
		|| (sh->cmd_table[i][j] == '-' && sh->cmd_table[i][j + 1] == '-')
		|| (ft_atoll(&sh->cmd_table[i][j]) < 0 && sh->cmd_table[i][j] != '-')
		|| !sh->cmd_table[i][j])
	{
		write(2, " numeric argument required\n", 26);
		terminate_struct(sh);
		free_arr(sh->envp);
		free(sh);
		exit (255);
	}
}

int	get_exit_code(t_shell *sh)
{
	int	status;

	status = 0;
	if (WIFEXITED(sh->status))
		status = WEXITSTATUS(sh->status);
	if (WIFSIGNALED(sh->status))
		status = WTERMSIG(sh->status);
	return (status);
}

void	right_exit_builtin(t_shell *sh, int i, int j)
{
	int	error;

	error = 0;
	while (sh->cmd_table[i][j] && sh->cmd_table[i][j++] != 1)
	j++;
	check_failing_exit(sh, i, j);
	error = ft_atoi(&sh->cmd_table[i][j]);
	terminate_struct(sh);
	free_arr(sh->envp);
	free(sh);
	exit (error);
}

void	exit_error(t_shell *sh, char **tmp, DIR *dir, int i)
{
	if (sh->infiles != NULL && sh->infiles->fd == -1)
		exit_status(sh, tmp, 1);
	if (((sh->exit_code == 127
				|| (dir != NULL
					&& ft_strchr(sh->path_to_file_table[i], '/') == 0)
				|| ft_strlen(sh->cmd_table[i]) == 0
				|| (ft_strnstr(sh->cmd_table[0], "./", 2) == NULL
					&& dir == NULL)
				|| check_dot(sh->cmd_table[i]))
			&& check_built_in_main(sh->cmd_table[i]) == false))
	{
		if (dir != NULL)
			closedir(dir);
		if (sh->cmd_table[i][0] == 1 && ft_strlen(sh->cmd_table[i]) == 1)
			exit_status(sh, tmp, 0);
		write(2, "minishell: command not found\n", 29);
		exit_status(sh, tmp, 127);
	}
	exit_status_helper(sh, tmp, dir, i);
}

void	exit_status(t_shell *sh, char **tmp, int status)
{
	terminate_struct(sh);
	if (tmp)
		free_arr(tmp);
	free_arr(sh->envp);
	free(sh);
	exit(status);
}
