/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:08:35 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/19 15:27:13 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	access_check(t_shell *sh, char *arg)
{
	int		i;
	char	*cmd;
	char	**path;

	i = 0;
	while (sh->envp[i] && ft_strncmp(sh->envp[i], "PATH", 4) != 0)
		i++;
	if (sh->envp[i])
		path = ft_split(sh->envp[i] + 5, ':');
	else
		path = NULL;
	i = 0;
	while (arg[i] && arg[i] != 1)
		i++;
	cmd = ft_substr(arg, 0, i);
	if (check_path(sh, path, cmd) == false)
		return (free(cmd), free_arr(path), false);
	return (free(cmd), free_arr(path), true);
}

bool	check_path(t_shell *sh, char **path, char *cmd)
{
	int			i;
	char		*cmd_path;

	i = 0;
	if (ft_strlen(cmd) == 0)
		return (false);
	if (access(cmd, F_OK) == 0 && check_binary(cmd) == true)
		return (sh->path_to_file_table[sh->index++] = ft_strdup(cmd), true);
	while (path && path[i] && ft_strchr(cmd, '/') == 0)
	{
		cmd_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin_free(cmd_path, cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			sh->path_to_file_table[sh->index++] = ft_strdup(cmd_path);
			return (free(cmd_path), true);
		}
		free(cmd_path);
		i++;
	}
	if (check_built_in_main(sh, cmd) == true)
		return (sh->path_to_file_table[sh->index++] = ft_strdup(""), true);
	return (sh->exit_code = 127, false);
}

bool	check_cmd(t_shell *sh)
{
	int	i;

	i = 0;
	sh->index = 0;
	while (sh->cmd_table[i])
	{
		if (access_check(sh, sh->cmd_table[i]) == false)
		{
			if (check_built_in_main(sh, sh->cmd_table[i]) == false
				&& check_built_in_child(sh, sh->cmd_table[i]) == false)
			{
				sh->path_to_file_table[sh->index] = NULL;
				return (false);
			}
		}
		i++;
	}
	sh->path_to_file_table[sh->index] = NULL;
	return (true);
}

bool	check_binary(char *cmd)
{
	char	cwd[PATH_MAX];
	char	*sys_dir[3];
	int		check_sys_dir;
	int		i;

	i = -1;
	check_sys_dir = 0;
	sys_dir[0] = "/bin";
	sys_dir[1] = "/usr/bin";
	sys_dir[2] = "/usr/local/bin";
	getcwd(cwd, sizeof(cwd));
	while (++i < 3)
	{
		if (ft_strncmp(cwd, sys_dir[i], 15) == 0)
			check_sys_dir = 1;
		if (check_bin_helper(sys_dir[i], cmd) == true)
			return (true);
	}
	if (check_sys_dir == 1 && access(cmd, F_OK) == 0)
		return (true);
	if (check_sys_dir == 0 && access(cmd, F_OK) == 0
		&& ft_strnstr(cmd, "./", 2) != NULL)
		return (true);
	return (false);
}

bool	check_bin_helper(char *sys_dir, char *cmd)
{
	if (ft_strncmp(cmd, sys_dir, 4) == 0 && access(cmd, F_OK) == 0)
		return (true);
	if (ft_strncmp(cmd, sys_dir, 8) == 0 && access(cmd, F_OK) == 0)
		return (true);
	if (ft_strncmp(cmd, sys_dir, 14) == 0 && access(cmd, F_OK) == 0)
		return (true);
	return (false);
}
