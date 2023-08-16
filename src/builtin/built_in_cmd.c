/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:02:53 by skunert           #+#    #+#             */
/*   Updated: 2023/08/16 19:23:48 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_echo(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i] && str[i] != ' ' && str[i] != 9 && str[i] != 2)
		i++;
	if (str[i] == 2)
		check = 1;
	i++;
	if (check == 1 || ft_check_flag(str, &i, &check) == false)
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
	while (str[i] != '\0' && str[i] != 32)
		i++;
	i++;
	if (str[i] == '\0')
		return ;
	if (str[i] == '=' || str[i] == 39)
	{
		write(2, " not a valid identifier\n", 24);
		sh->status = 1;
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
	int		new;
	char	*tmp;

	i = 0;
	if (sh == NULL)
		return ;
	while (str[i] && (str[i] != 32 && str[i] != 9))
		i++;
	i++;
	new = i;
	if (!str[i] || ft_isalpha(str[i]) == 0)
		return (sh->status = 1, (void)write(2, " not a valid identifier\n", 24));
	tmp = ft_substr(str, i, count_until_space(&str[i]));
	tmp = ft_strjoin_free(tmp, "=");
	i = 0;
	while (sh->envp && sh->envp[i]
		&& ft_strncmp(sh->envp[i], tmp, ft_strlen(tmp)))
		i++;
	free(tmp);
	if (!sh->envp || sh->envp[i] == NULL)
		return ;
	unset_helper(sh, i, new, str);
}

void	handle_cd(t_shell *sh, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strlen(str) == 2)
	{
		go_to_home(sh);
		return ;
	}
	while (str[i] && str[i] != ' ')
		i++;
	tmp = ft_substr(str, i + 1, ft_strlen(str));
	if (chdir(tmp) == -1)
	{
		sh->status = 1;
		perror("chdir");
	}
	change_pwd(sh);
	free(tmp);
}
