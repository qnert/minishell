/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:44:58 by skunert           #+#    #+#             */
/*   Updated: 2023/08/14 15:01:55 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	change_pwd(t_shell *sh)
{
	int		i;
	char	cwd[256];

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	while (sh->envp && sh->envp[i] && ft_strncmp(sh->envp[i], "PWD=", 4))
		i++;
	if (!sh->envp || !sh->envp[i])
		return ;
	free(sh->envp[i]);
	sh->envp[i] = ft_strjoin("PWD=", cwd);
}

void	replace_space_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
			str[i] = 1;
		i++;
	}
}
