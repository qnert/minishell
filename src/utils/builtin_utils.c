/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:55:43 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/22 01:44:33 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	go_to_home(t_shell *sh)
{
	char	*tmp;

	tmp = get_home_from_env(sh);
	if (tmp == NULL)
		return ((void)write(2, "miniHell: cd: HOME not set\n", 27));
	if (chdir(tmp) != 0)
	{
		free(tmp);
		perror("cd");
		return ;
	}
	free(tmp);
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

int	count_until_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != 32)
		i++;
	return (i);
}

void	unset_helper(t_shell *sh, int i, int new, char *str)
{
	char	*tmp;

	if (!sh->envp || sh->envp[i] == NULL)
		return ;
	erase_env_var(sh, i);
	tmp = &str[new + count_until_space(&str[new])];
	if (sh->check == 1)
		free(str);
	if (ft_strchr(tmp, ' ') && ft_strlen(tmp) != 6)
	{
		sh->check = 1;
		handle_unset(sh, ft_strjoin_free(ft_strdup("unset"), tmp));
	}
	sh->status = 0;
}

bool	check_special_char(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i + 1] == '=')
		return (true);
	tmp = ft_substr(str, 0, i);
	if (ft_strchr(tmp, '-') || ft_strchr(tmp, '+') || ft_strchr(tmp, '.')
		|| ft_strchr(tmp, '{') || ft_strchr(tmp, '}') || ft_strchr(tmp, '*')
		|| ft_strchr(tmp, '#') || ft_strchr(tmp, '!') || ft_strchr(tmp, '@')
		|| ft_strchr(tmp, '^') || ft_strchr(tmp, '~') || ft_strchr(tmp, '*')
		|| ft_strchr(tmp, ';'))
		return (free(tmp), true);
	return (free(tmp), false);
}
