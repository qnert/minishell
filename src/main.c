/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/17 12:58:37 by njantsch         ###   ########.fr       */
=======
/*   Updated: 2023/07/17 15:40:56 by skunert          ###   ########.fr       */
>>>>>>> 84000c90ff3ed8e479c384c5981982ca46aa38f3
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
<<<<<<< HEAD
		if (!(handle_build_in(str)))
			return;
		free(str);
=======
		parser_main(str, sh);
		free_arr(sh->cmd_table);
>>>>>>> 84000c90ff3ed8e479c384c5981982ca46aa38f3
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
