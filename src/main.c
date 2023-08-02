/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
/*   Updated: 2023/08/01 15:18:27 by njantsch         ###   ########.fr       */
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

void	print_list(t_files *lst)
{
	t_files	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->file_name)
			printf("%s %d\n", curr->file_name, curr->pos);
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
				printf("minishell: syntax error near unexpected token\n");
			else
				execute_main(sh);
		}
		// printf("amount of pipes: %d\n", sh->pipes);
		// print_matrix(sh->cmd_table);
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
	terminate_struct(sh);
	free(sh->envp);
	free(sh);
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
		set_signals();
		sh = shell_init(envp);
		shell_loop(sh);
	}
	return (0);
}
