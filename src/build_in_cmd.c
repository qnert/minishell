/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:02:53 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 17:55:03 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != 9)
		i++;
	while (str[i] == ' ' || str[i] == 9)
		i++;
	if (str[i] != '\0' && str[i + 1] != '\0'
		&& (str[i] == '-' && str[i + 1] == 'n'))
	{
		i = i + 2;
		while (str[i] && (str[i] == ' ' || str[i] == 9))
			i++;
		printf("%s", &str[i]);
		return ;
	}
	printf("%s\n", &str[i]);
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
