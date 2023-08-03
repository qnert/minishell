/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:39:05 by skunert           #+#    #+#             */
/*   Updated: 2023/08/03 17:57:02 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_built_in_child(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		return (true);
	if (ft_strncmp(str, "exit", 4) == 0)
		return (true);
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (true);
	if (ft_strncmp(str, "env", 3) == 0 && ft_strlen(str) == 3)
		return (true);
	return (false);
}

bool	check_built_in_main(char *str)
{
	if (ft_strncmp(str, "cd", 2) == 0)
		return (true);
	if (ft_strncmp(str, "export", 6) == 0)
		return (true);
	if (ft_strncmp(str, "unset", 5) == 0)
		return (true);
	return (false);
}

void	check_exit(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	while (sh->cmd_table[i])
	{
		j = 0;
		if (ft_strncmp(sh->cmd_table[i], "exit", 4) == 0)
		{
			right_exit_builtin(sh, i, j);
		}
		i++;
	}
}

void	handle_built_in(t_shell *sh, char *str)
{
	replace_split_char(str);
	if (ft_strncmp(str, "cd", 2) == 0)
		handle_cd(sh, str);
	if (ft_strncmp(str, "echo", 4) == 0)
		handle_echo(str);
	if (ft_strncmp(str, "exit", 4) == 0)
	{
		terminate_struct(sh);
		free_arr(sh->envp);
		free(sh);
		exit (EXIT_SUCCESS);
	}
	if (ft_strncmp(str, "env", 3) == 0)
		print_matrix(sh->envp);
	if (ft_strncmp(str, "pwd", 3) == 0)
		handle_pwd();
	if (ft_strncmp(str, "export", 6) == 0)
		handle_export(sh, str);
	if (ft_strncmp(str, "unset", 5) == 0)
		handle_unset(sh, str);
}
