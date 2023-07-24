/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:39:05 by skunert           #+#    #+#             */
/*   Updated: 2023/07/24 18:46:30 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_build_in(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		return (true);
	if (ft_strncmp(str, "exit", 4) == 0)
		return (true);
	if (ft_strncmp(str, "cd", 2) == 0)
		return (true);
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (true);
	if (ft_strncmp(str, "export", 6) == 0)
		return (true);
	if (ft_strncmp(str, "unset", 5) == 0)
		return (true);
	if (ft_strncmp(str, "env", 3) == 0)
		return (true);
	return (false);
}

void	handle_build_in(t_shell *sh, char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		handle_echo(str);
	if (ft_strncmp(str, "exit", 4) == 0)
		exit (0);
	if (ft_strncmp(str, "env", 3) == 0)
		print_matrix(sh->envp);
	if (ft_strncmp(str, "pwd", 3) == 0)
		handle_pwd();
	if (ft_strncmp(str, "export", 6) == 0)
		handle_export(sh, str);
	if (ft_strncmp(str, "unset", 5) == 0)
		handle_unset(sh, str);
}
