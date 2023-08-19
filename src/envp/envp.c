/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:25:45 by skunert           #+#    #+#             */
/*   Updated: 2023/08/17 18:49:55 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_envp_name(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1] != '=')
		i++;
	return (ft_substr(str, 0, i + 1));
}

char	**cpy_envp(char **envp)
{
	int		i;
	char	*str;
	char	**envp_cpy;

	i = 0;
	envp_cpy = ft_calloc(get_len_matrix(envp) + 1, sizeof(char *));
	while (envp[i] != NULL)
	{
		str = get_envp_name(envp[i]);
		envp_cpy[i] = getenv(str);
		str = ft_strjoin_free(str, "=");
		envp_cpy[i] = ft_strjoin_free(str, envp_cpy[i]);
		i++;
	}
	envp_cpy[i] = NULL;
	return (envp_cpy);
}

void	change_env_vars(t_shell *sh, int index)
{
	free(sh->envp[index]);
	while (sh->envp[index] != NULL)
	{
		if (sh->envp[index + 1] != NULL)
		{
			sh->envp[index] = ft_strdup(sh->envp[index + 1]);
			free(sh->envp[index + 1]);
		}
		else
			sh->envp[index] = NULL;
		index++;
	}
}

void	erase_env_var(t_shell *sh, int index)
{
	if (index == get_len_matrix(sh->envp) - 1)
	{
		free(sh->envp[index]);
		sh->envp[index] = NULL;
		return ;
	}
	change_env_vars(sh, index);
}

char	*change_str_to_env(t_shell *sh, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strchr(str, '$') == 0)
		return (str);
	if (str[i] == '$' && str[i + 1] == '?')
		return (get_exit_code_string(sh, str));
	if (ft_strlen(str) == 1 && str[i] == '$')
		return (str);
	if (ft_strlen(str) == 1 && !ft_isalnum(str[i]))
		return (str);
	str = ft_strjoin_free(str, "=");
	while (sh->envp && sh->envp[i]
		&& ft_strncmp(sh->envp[i], str + 1, ft_strlen(str) - 1) != 0)
		i++;
	if (!sh->envp || !sh->envp[i])
		return (free(str), ft_strdup(""));
	while (sh->envp[i][j] != '=')
		j++;
	free(str);
	return (ft_substr(sh->envp[i], j + 1, ft_strlen(sh->envp[i]) - j + 1));
}
