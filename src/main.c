/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
/*   Updated: 2023/07/13 14:08:44 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_loop(void)
{
	char	*str;

	str = readline("miniHell > ");
	while (str != NULL)
	{
		if (!(handle_build_in(str)))
			return ;
		free(str);
		str = readline("miniHell > ");
	}
	free(str);
	return ;
}

int	main(int argc, char **argv)
{
	if (argc != 1 && argv == NULL)
	{
		printf("Wrong amount of arguments!\n");
		return (-1);
	}
	else
		shell_loop();
	return (0);
}
