/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:19:28 by skunert           #+#    #+#             */
/*   Updated: 2023/08/08 12:14:41 by skunert          ###   ########.fr       */
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
		if (sh->cmd_table[i][ft_strlen(sh->cmd_table[i]) - 1] == '8'
			|| ft_isalpha(sh->cmd_table[i][j])
			|| sh->cmd_table[i][ft_strlen(sh->cmd_table[i]) - 1] == '9')
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
		if (ft_strlen(curr->str) != 0 && curr->next && curr->next->token == 7 && ft_strlen(curr->next->str) <= 1 && ft_isalpha(curr->next->str[0]))
			sh->cmd_table[++(*i)] = ft_strdup(curr->str);
		else if (ft_strlen(curr->str) != 0 && curr->next && curr->next->token != 4)
			sh->cmd_table[++(*i)] = ft_strjoin_free(ft_strdup(curr->str), "\1");
		else
			sh->cmd_table[++(*i)] = ft_strdup(curr->str);
		sh->check = 1;
	}
	else if ((check_word_token(curr->token)
			&& curr->next == NULL) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free(sh->cmd_table[(*i)], curr->str);
	else if ((curr->token == 0 && (curr->next != NULL
				&& curr->next->token == 0)) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free
			(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
	else if ((curr->token == 0 && (curr->next != NULL && ft_strlen(curr->next->str) > 1 && (curr->next->token
					== 6 || curr->next->token == 7))) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free
			(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
	else if ((curr->token == 0 && (curr->next != NULL && (curr->next->token
					== 6 || curr->next->token == 7))) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free(sh->cmd_table[(*i)], curr->str);
	else if (((curr->token == 6 || curr->token == 7) && (curr->next
				!= NULL && curr->next->token == 0)) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free
			(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
	else if (((curr->token == 6 || curr->token == 7) && (curr->next
				!= NULL && (curr->next->token == 6 || curr->next->token == 7))) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free
			(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
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
