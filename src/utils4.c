/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:15:27 by skunert           #+#    #+#             */
/*   Updated: 2023/07/27 14:15:39 by skunert          ###   ########.fr       */
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
