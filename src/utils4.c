/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:15:27 by skunert           #+#    #+#             */
/*   Updated: 2023/07/31 11:49:18 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

bool	ft_check_flag(char *str, int *i, int *check)
{
	int	tmp;

	tmp = 0;
	if (str[*i] != '-')
		return (false);
	while (str[*i] && str[*i] == '-')
	{
		(*i)++;
		while (str[*i] && str[*i] != 32)
		{
			if (str[*i] == 'n')
				(*i)++;
			else
			{
				*i = tmp;
				return (true);
			}
		}
		(*i)++;
		tmp = (*i);
	}
	(*check) = 1;
	printf("%s", &str[*i]);
	return (true);
}

char	*ft_charjoin_free(char *str, char c)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	while (str[++i])
		tmp[i] = str[i];
	tmp[i] = c;
	tmp[++i] = '\0';
	free(str);
	return (tmp);
}
