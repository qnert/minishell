/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:19:28 by skunert           #+#    #+#             */
/*   Updated: 2023/08/13 13:20:08 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atoll(const char *str);

void	check_failing_exit(t_shell *sh, int i, int j)
{
	if (ft_strchr(&sh->cmd_table[i][j], 1) != 0
		&& !ft_isalpha(sh->cmd_table[i][j]))
	{
		write(2, " too many arguments\n", 20);
		terminate_struct(sh);
		free_arr(sh->envp);
		free(sh);
		exit (1);
	}
	if (ft_isalpha(sh->cmd_table[i][j]) || ft_atoll(&sh->cmd_table[i][j])
		>= 9223372036854775807 || (sh->cmd_table[i][j] == '+' && sh->cmd_table[i][j + 1] == '+')
		|| (sh->cmd_table[i][j] == '-' && sh->cmd_table[i][j + 1] == '-')
		|| (ft_atoll(&sh->cmd_table[i][j]) < 0 && sh->cmd_table[i][j] != '-')
		|| !sh->cmd_table[i][j])
	{
		write(2, " numeric argument required\n", 26);
		terminate_struct(sh);
		free_arr(sh->envp);
		free(sh);
		exit (255);
	}
}

void	concat_right(t_shell *sh, t_lexer *curr, int *i)
{
	if (check_word_token(curr->token) && sh->check == 0)
	{
		if (curr->token == 0 && curr->next && curr->next->token == 0)
			sh->cmd_table[++(*i)] = ft_strjoin_free(ft_strdup(curr->str), "\1");
		else if ((curr->token == 6 || curr->token == 7) && curr->b_space == 1)
			sh->cmd_table[++(*i)] = ft_strjoin_free(ft_strdup(curr->str), "\1");
		else
			sh->cmd_table[++(*i)] = ft_strdup(curr->str);
		sh->check = 1;
	}
	else if ((curr->token == 6 || curr->token == 7) && curr->f_space == 1 && curr->b_space == 0)
			sh->cmd_table[(*i)] = ft_strjoin_free(ft_strjoin_free(sh->cmd_table[(*i)], "\1"), curr->str);
	else if ((check_word_token(curr->token)
			&& curr->next == NULL) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free(sh->cmd_table[(*i)], curr->str);
	else if (curr->token == 0 && curr->next && curr->next->token == 0
			&& ft_strlen(curr->str) != 0)
		sh->cmd_table[(*i)] = ft_strjoin_free(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
	else if ((curr->token == 6 || curr->token == 7) && curr->next != NULL
			&& curr->b_space == 1 && curr->f_space == 0 && ft_strlen(curr->str) != 0)
			sh->cmd_table[(*i)] = ft_strjoin_free(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
	else if ((curr->token == 6 || curr->token == 7) && curr->next != NULL
			&& curr->b_space == 1 && curr->f_space == 1 && ft_strlen(curr->str) != 0)
			sh->cmd_table[(*i)] = ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(sh->cmd_table[(*i)], "\1"), curr->str), "\1");
	else if (check_word_token(curr->token)
		&& (curr->next != NULL) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free(sh->cmd_table[(*i)], curr->str);
}

void	right_exit_builtin(t_shell *sh, int i, int j)
{
	int	error;

	error = 0;
	while (sh->cmd_table[i][j] && sh->cmd_table[i][j++] != 1)
	j++;
	check_failing_exit(sh, i, j);
	error = ft_atoi(&sh->cmd_table[i][j]);
	terminate_struct(sh);
	free_arr(sh->envp);
	free(sh);
	exit (error);
}

bool	check_file_token(int token)
{
	if (token == 2 || token == 3)
		return (true);
	if (token == 4 || token == 5)
		return (true);
	return (false);
}

void	change_f_b_spaces(t_lexer *lst, char *str, int i, int start)
{
	t_lexer	*curr;

	curr = lst;
	while(curr->next)
		curr = curr->next;
	if (str[start - 2] && str[start - 2] == ' ')
		curr->f_space = 1;
	if (str[i + 1] && str[i + 1] == ' ')
		curr->b_space = 1;
}
