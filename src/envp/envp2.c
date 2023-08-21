/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:42:55 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/21 13:26:39 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	check_existence_env(t_shell *sh, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if ((str[i] == '\0' && str[i] != '=') || str[i - 1] == '?')
	{
		if (ft_isalpha(str[i - 1]) && str[i] == '\0')
			return (true);
		write(2, "minishell: not a valid identifier\n", 35);
		sh->status = 1;
		return (true);
	}
	tmp = ft_substr(str, 0, i + 1);
	i = 0;
	while (sh->envp[i] && ft_strncmp(sh->envp[i], tmp, ft_strlen(tmp)))
		i++;
	if (sh->envp[i] == NULL)
		return (free(tmp), false);
	free(sh->envp[i]);
	sh->envp[i] = ft_strdup(str);
	return (free(tmp), true);
}

char	*get_home_from_env(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->envp && sh->envp[i] && ft_strncmp(sh->envp[i], "HOME=", 5) != 0)
		i++;
	if (sh->envp && sh->envp[i])
		return (ft_substr(sh->envp[i], 5, ft_strlen(sh->envp[i])));
	return (NULL);
}

char	*getenv_own(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	return (ft_substr(str, i, ft_strlen(str) + 1));
}

char	**cpy_envp_add(char **envp, char *tmp)
{
	int		i;
	char	*str;
	char	**envp_cpy;

	i = 0;
	envp_cpy = ft_calloc(get_len_matrix(envp) + 2, sizeof(char *));
	while (envp[i] != NULL)
	{
		str = get_envp_name(envp[i]);
		envp_cpy[i] = getenv(str);
		if (!envp_cpy[i])
			envp_cpy[i] = getenv_own(envp[i]);
		str = ft_strjoin_free(str, "=");
		envp_cpy[i] = ft_strjoin_free(str, envp_cpy[i]);
		i++;
	}
	envp_cpy[i] = tmp;
	envp_cpy[i + 1] = NULL;
	free_arr(envp);
	return (envp_cpy);
}
