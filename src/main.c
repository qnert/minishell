/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
/*   Updated: 2023/07/21 17:33:01 by skunert          ###   ########.fr       */
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
			if (lexer(sh, str) == false || parser_main(sh) == false)
			{
				printf("false\n");
				terminate_struct(sh);
			}
			else
				printf("true\n");
		}
		if (sh->infile != NULL)
			printf("infile: %s\n", sh->infile);
		if (sh->here_doc_delim != NULL)
			printf("here_doc_delim: %s\n", sh->here_doc_delim);
		if (sh->token_list != NULL && sh->token_list->str != NULL)
		{
			print_list(sh->token_list);
			terminate_struct(sh);
		}
		return ;
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
