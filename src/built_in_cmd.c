/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:02:53 by skunert           #+#    #+#             */
/*   Updated: 2023/07/26 17:29:57 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_echo(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i] && str[i] != ' ' && str[i] != 9)
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == 9))
		i++;
	if (ft_check_flag(str, &i, &check) == false)
		printf("%s\n", &str[i]);
	else if (check == 0)
		printf("%s", &str[i]);
}

void	handle_pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", cwd);
}

void	handle_export(t_shell *sh, char *str)
{
	int		i;
	int		len;

	i = 0;
	len = get_len_matrix(sh->envp);
	while (str[i] != '\0' && str[i] != 32 && str[i] != 9)
		i++;
	while (str[i] && (str[i] == 32 || str[i] == 9))
		i++;
	if (!str[i])
		return ;
	if (ft_strrchr(&str[i], ' ') != 0)
	{
		printf("bad assignment\n");
		return ;
	}
	if (check_existence_env(sh, &str[i]) == false)
	{
		sh->envp[len] = ft_strdup(&str[i]);
		sh->envp[len + 1] = NULL;
	}
}

void	handle_unset(t_shell *sh, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (sh == NULL)
		return ;
	while (str[i] && (str[i] != 32 && str[i] != 9))
		i++;
	while (str[i] && (str[i] == 32 || str[i] == 9))
		i++;
	tmp = ft_substr(str, i, ft_strlen(str) - i);
	tmp = ft_strjoin_free(tmp, "=");
	i = 0;
	while (sh->envp && sh->envp[i]
		&& ft_strncmp(sh->envp[i], tmp, ft_strlen(tmp)))
		i++;
	if (!sh->envp || sh->envp[i] == NULL)
	{
		free(tmp);
		return ;
	}
	erase_env_var(sh, i);
}

void	handle_cd(t_shell *sh, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strlen(str) == 2)
	{
		tmp = get_home_from_env(sh);
		if (!tmp)
		{
			write(2, "miniHell: cd: HOME not set\n", 27);
			return ;
		}
		if (chdir(tmp) != 0)
		{
			free(tmp);
			perror("cd");
		}
		return ;
	}
	while (str[i] && (str[i] < 9 || str[i] > 13) && str[i] != 32)
		i++;
	tmp = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (chdir(tmp) != 0)
		perror("cd");
	free(tmp);
}
