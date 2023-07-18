/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:39:05 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 13:10:44 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_build_in(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(str, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(str, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	if (ft_strncmp(str, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(str, "env", 3) == 0)
		return (1);
	return (0);
}
