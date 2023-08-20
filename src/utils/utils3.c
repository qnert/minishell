/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:50:23 by skunert           #+#    #+#             */
/*   Updated: 2023/08/20 19:09:54 by njantsch         ###   ########.fr       */
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

char	*readline_or_gnl(void)
{
	char	*str;

	if (!isatty(0))
	{
		str = get_next_line(0);
		if (str)
			str = ft_strtrim(str, "\n");
	}
	else
		str = readline("miniHell > ");
	return (str);
}
