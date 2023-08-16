/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:42:55 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/16 10:55:02 by njantsch         ###   ########.fr       */
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
		write(2, " not a valid identifier\n", 24);
		sh->status = 1;
		return (true);
	}
	tmp = ft_substr(str, 0, i);
	i = 0;
	while (sh->envp[i] && ft_strncmp(sh->envp[i], tmp, ft_strlen(tmp)))
		i++;
	if (sh->envp[i] == NULL)
		return (false);
	free(sh->envp[i]);
	sh->envp[i] = ft_strdup(str);
	return (true);
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
