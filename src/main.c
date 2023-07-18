/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 12:58:15 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	shell_loop(t_shell *sh)
{
	char	*str;

	str = readline("miniHell > ");
	while (str != NULL)
	{
		if (str[0] != '\0')
		{
			parser_main(str, sh);
			free_arr(sh->cmd_table);
		}
		return ;
		str = readline("miniHell > ");
	}
	free(str);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	sh = NULL;
	if (argc != 1 && argv == NULL)
	{
		printf("Wrong amount of arguments!\n");
		return (-1);
	}
	else
	{
		sh = shell_init(envp);
		shell_loop(sh);
	}
	return (0);
}
