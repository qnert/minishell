/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:02:53 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 15:19:54 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != 9)
		i++;
	while (str[i] == ' ' || str[i] == 9)
		i++;
	if (str[i] != '\0' && str[i + 1] != '\0'
		&& (str[i] == '-' && str[i + 1] == 'n'))
	{
		i = i + 2;
		while (str[i] && (str[i] == ' ' || str[i] == 9))
			i++;
		printf("%s", &str[i]);
		return ;
	}
	printf("%s\n", &str[i]);
}
