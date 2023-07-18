/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:25:45 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 12:54:05 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	envp_cpy = ft_calloc(get_len_matrix(envp), sizeof(char *));
	while (envp[i] != NULL)
	{
		str = get_envp_name(envp[i]);
		envp_cpy[i] = getenv(str);
		str = ft_strjoin_free(str, "=");
		envp_cpy[i] = ft_strjoin_free(str, envp_cpy[i]);
		i++;
	}
	return (envp_cpy);
}
