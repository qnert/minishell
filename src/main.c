/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
/*   Updated: 2023/08/20 19:08:45 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32)
			return (1);
		i++;
	}
	return (0);
}

void	do_operation(t_shell *sh, char *str)
{
	add_history(str);
	if (lexer(sh, str) == false)
	{
		write(2, "minishell: parse error\n", 23);
		sh->status = 2;
	}
	else if (parser_main(sh) == false)
	{
		write(2, "minishell: parse error\n", 23);
		sh->status = 2;
	}
	else
		execute_main(sh);
}

int	shell_loop(t_shell *sh)
{
	int		tmp;
	char	*str;

	if (sh == NULL)
		return (0);
	str = readline_or_gnl();
	while (str != NULL)
	{
		if (check_spaces(str) && str[0] != '\0')
			do_operation(sh, str);
		terminate_struct(sh);
		free(str);
		str = readline_or_gnl();
	}
	tmp = sh->status;
	terminate_struct(sh);
	free(sh->envp);
	free(sh);
	rl_clear_history();
	free(str);
	return (tmp);
}

int	main(int argc, char **argv, char **envp)
{
	int		tmp;
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
		tmp = shell_loop(sh);
	}
	return (tmp);
}
