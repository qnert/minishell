/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:50:23 by skunert           #+#    #+#             */
/*   Updated: 2023/08/21 13:21:12 by skunert          ###   ########.fr       */
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

int	count_equal(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '=')
			count++;
		i++;
	}
	return (count);
}
