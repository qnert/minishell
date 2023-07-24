/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
/*   Updated: 2023/07/24 18:44:48 by skunert          ###   ########.fr       */
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

void	print_list(t_lexer *lst)
{
	t_lexer	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->str)
			printf("%s %d\n", curr->str, curr->token);
		curr = curr->next;
	}
}

void	shell_loop(t_shell *sh)
{
	char	*str;

	if (sh == NULL)
		return ;
	str = readline("miniHell > ");
	while (str != NULL)
	{
		if (str[0] != '\0')
		{
			add_history(str);
			if (lexer(sh, str) == false)
				printf("false\n");
			else if (parser_main(sh) == false)
				printf("false\n");
			else
				execute_main(sh);
		}
		// printf("amount of pipes: %d\n", sh->pipes);
		// print_marix(sh->cmd_table);
		// if (sh->outfiles != NULL)
		// {
		// 	printf("outfile: %s\n", sh->outfiles->file_name);
		// 	printf("fd: %d\n", sh->outfiles->fd);
			// if (sh->infiles->delim != NULL)
			// {
			// 	printf("delim: %s\n", sh->infiles->delim);
			// 	unlink(sh->infiles->file_name);
			// }
		// if (sh->token_list != NULL && sh->token_list->str != NULL)
		// {
		// 	print_list(sh->token_list);
		// 	terminate_struct(sh);
		// }
		terminate_struct(sh);
		str = readline("miniHell > ");
	}
	rl_clear_history();
	free(str);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	sh = NULL;
	if (argc != 1 || argv == NULL)
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
