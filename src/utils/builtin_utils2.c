/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:09:18 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/22 16:12:33 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_old_pwd(t_shell *sh)
{
	char	cwd[256];
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	tmp = NULL;
	while (sh->envp && sh->envp[i] && ft_strncmp(sh->envp[i], "PWD=", 4))
		i++;
	if (!sh->envp || !sh->envp[i])
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return (perror("getcwd() error"));
	}
	else
		tmp = ft_substr(sh->envp[i], 4, ft_strlen(sh->envp[i]) - 4);
	set_old_pwd(sh, tmp, path, cwd);
}

void	set_old_pwd(t_shell *sh, char *tmp, char *path, char *cwd)
{
	int	i;

	i = 0;
	while (sh->envp && sh->envp[i] && ft_strncmp(sh->envp[i], "OLDPWD=", 7))
		i++;
	if (!sh->envp || !sh->envp[i])
	{
		if (!tmp)
			path = ft_strjoin_free(ft_strdup("OLDPWD="), cwd);
		else
			path = ft_strjoin_free(ft_strdup("OLDPWD="), tmp);
		tmp = ft_strjoin_free(ft_strdup("export "), path);
		handle_export(sh, tmp);
		free(path);
		free(tmp);
		return ;
	}
	free(sh->envp[i]);
	if (!tmp)
		sh->envp[i] = ft_strjoin("OLDPWD=", cwd);
	else
	{
		sh->envp[i] = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
	}
}

void	handle_old_pwd(t_shell *sh)
{
	int		i;
	char	*str;

	i = 0;
	while (sh->envp && sh->envp[i] && ft_strncmp(sh->envp[i], "OLDPWD=", 7))
		i++;
	if (!sh->envp || !sh->envp[i])
		return (sh->status = 1,
			(void)write(2, "minishell: OLDPWD not set\n", 27));
	str = ft_substr(sh->envp[i], 7, ft_strlen(sh->envp[i]) - 7);
	if (chdir(str) == -1)
	{
		sh->status = 1;
		perror("chdir");
	}
	else
	{
		printf("%s\n", str);
		sh->status = 0;
	}
	if (str)
		free(str);
}
