/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
/*   Updated: 2023/07/05 14:44:19 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char	*str;

	str = readline("miniHell > ");
	while (str != NULL)
	{
		if (ft_strncmp(str, "echo", 4) == 0)
			ft_printf("%s\n", str + 5);
		str = readline("miniHell > ");
		free(str);
	}
	return (0);
}
