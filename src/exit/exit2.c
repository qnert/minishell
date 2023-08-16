/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:45:40 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/16 18:41:38 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_exit_code_string(t_shell *sh, char *str)
{
	int		i;
	char	*tmp;
	char	*status;
	char	*res;

	i = 2;
	status = ft_itoa(sh->status);
	if (!str[i])
		return (status);
	while (str[i] && str[i] != '$')
		i++;
	tmp = ft_substr(str, 2, i - 2);
	res = ft_strjoin_free(status, tmp);
	free(tmp);
	return (res);
}

void	exit_status_helper(t_shell *sh, char **tmp, DIR *dir, int i)
{
	if (sh->exit_code == 1)
		exit_status(sh, tmp, 1);
	if (sh->path_to_file_table[0] == NULL && dir == NULL)
		exit_status(sh, tmp, 0);
	if (access(sh->path_to_file_table[i], X_OK) == -1
		&& check_built_in_main(sh->cmd_table[i]) == false)
	{
		write(2, "minishell: non executable\n", 26);
		exit_status(sh, tmp, 126);
	}
	if (dir != NULL)
	{
		closedir(dir);
		write(2, "minishell: is a directory\n", 26);
		exit_status(sh, tmp, 126);
	}
	exit_status(sh, tmp, 1);
}
