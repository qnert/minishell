/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
/*   Updated: 2023/08/16 12:51:43 by skunert          ###   ########.fr       */
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
			printf("%s %d %d %d\n", curr->str, curr->token, curr->f_space, curr->b_space);
		curr = curr->next;
	}
}

int		check_spaces(char *str)
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

int	shell_loop(t_shell *sh)
{
	int		tmp;
	char	*str;

	if (sh == NULL)
		return (0);
	if (!isatty(0))
	{
		str = get_next_line(0);
		if (str)
			str = ft_strtrim(str, "\n");
	}
	else
		str = readline("miniHell > ");
	while (str != NULL)
	{
		if (check_spaces(str) && str[0] != '\0')
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
		// printf("amount of pipes: %d\n", sh->pipes);
		// replace_split_char(sh->cmd_table[0]);
		// printf("%zu\n", ft_strlen(sh->cmd_table[0]));
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
		// }
		terminate_struct(sh);
		if (!isatty(0))
		{
			free(str);
			str = get_next_line(0);
			if (str)
				str = ft_strtrim(str, "\n");
		}
		else
			str = readline("miniHell > ");
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
