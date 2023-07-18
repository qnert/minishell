/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:08:35 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/18 13:43:02 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	access_check(t_shell *sh, char *arg)
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
	while (arg[i] && arg[i] != ' ')
		i++;
	cmd = ft_substr(arg, 0, i);
	if (check_path(sh, path, cmd) == 1)
		return (free(cmd), free_arr(path), 1);
	return (free(cmd), free_arr(path), 0);
}

int	check_path(t_shell *sh, char **path, char *cmd)
{
	int			i;
	static	int	j;
	char		*cmd_path;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
	{
		sh->path_to_file_table[j++] = ft_strdup(cmd);
		return (0);
	}
	while (path && path[i])
	{
		cmd_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin_free(cmd_path, cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			sh->path_to_file_table[j++] = ft_strdup(cmd_path);
			return (free(cmd_path), 0);
		}
		free(cmd_path);
		i++;
	}
	return (1);
}
