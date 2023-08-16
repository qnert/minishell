/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:08:35 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/16 12:40:04 by skunert          ###   ########.fr       */
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
	if (access(cmd, F_OK) == 0)
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
	if (check_built_in_main(cmd) == true)
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
			if (check_built_in_main(sh->cmd_table[i]) == false
				&& check_built_in_child(sh->cmd_table[i]) == false)
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