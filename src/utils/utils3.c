/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:50:23 by skunert           #+#    #+#             */
/*   Updated: 2023/08/18 16:52:18 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	check_dot(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '.')
			return (false);
		i++;
	}
	return (true);
}
