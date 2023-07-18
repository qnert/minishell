/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:25:45 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 12:54:13 by njantsch         ###   ########.fr       */
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
