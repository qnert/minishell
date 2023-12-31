/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:27:58 by skunert           #+#    #+#             */
/*   Updated: 2023/08/21 23:44:24 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	read_till_limiter(t_shell *sh, t_files *curr)
{
	char	*line;

	g_cntrlc = false;
	signal(SIGINT, sig_handler_heredoc);
	line = get_next_line(STDIN_FILENO);
	rtl_loop(sh, curr, line);
	signal(SIGINT, sig_handler);
	if (g_cntrlc == false)
	{
		close(curr->fd);
		curr->fd = open(curr->file_name, O_RDONLY);
	}
	unlink(curr->file_name);
}

void	check_and_write_here_doc(t_shell *sh, t_files *infiles)
{
	t_files	*curr;

	curr = infiles;
	while (curr)
	{
		if (curr->delim != NULL)
			read_till_limiter(sh, curr);
		curr = curr->next;
	}
}

t_lexer	*get_right_start_point(t_shell *sh)
{
	t_lexer	*curr;
	t_lexer	*tmp;

	curr = sh->token_list;
	if (!sh->infiles || !sh->infiles->next || sh->pipes == 0)
		return (curr);
	if (sh->outfiles->pos == sh->outfiles->next->pos)
		return (curr);
	while (curr)
	{
		if (curr->token > 3 && curr->token < 6)
			tmp = curr;
		curr = curr->next;
	}
	curr = tmp;
	sh->pipes = 0;
	while (curr)
	{
		if (curr->token == PIPE)
			sh->pipes++;
		curr = curr->next;
	}
	return (tmp);
}

void	concat_right_helper(t_shell *sh, t_lexer *curr, int *i)
{
	if (curr->token == 0 && curr->next
		&& (curr->next->token == 6 || curr->next->token == 7)
		&& curr->next->f_space == 1
		&& (curr->next == NULL || curr->b_space == 0))
		sh->cmd_table[(*i)] = ft_strjoin_free
			(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
	else if ((curr->token == 6 || curr->token == 7)
		&& curr->f_space == 1 && (curr->next == NULL || curr->b_space == 0))
		sh->cmd_table[(*i)] = ft_strjoin_free(sh->cmd_table[(*i)], curr->str);
	else if ((check_word_token(curr->token)
			&& curr->next == NULL) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free(sh->cmd_table[(*i)], curr->str);
	else if (curr->token == 0 && curr->next && curr->next->token == 0
		&& ft_strlen(curr->str) != 0 && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free
			(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
	else
		concat_right_helper2(sh, curr, i);
}

void	concat_right(t_shell *sh, t_lexer *curr, int *i)
{
	if (check_word_token(curr->token) && sh->check == 0)
	{
		if (curr->token == 0 && curr->next
			&& curr->next->token == 0)
			sh->cmd_table[++(*i)] = ft_strjoin_free
				(ft_strdup(curr->str), "\1");
		else if (check_word_token(curr->token)
			&& !ft_strncmp(curr->str, "echo", 4)
			&& curr->next
			&& (curr->next->token == 6 || curr->next->token == 7)
			&& !ft_strncmp(curr->next->str, "-n", 2))
			sh->cmd_table[++(*i)] = ft_strjoin_free(ft_strdup(curr->str), "\2");
		else if ((curr->token == 6 || curr->token == 7) && curr->b_space == 1)
			sh->cmd_table[++(*i)] = ft_strjoin_free(ft_strdup(curr->str), "\1");
		else if (curr->token == 0 && curr->next
			&& curr->next->f_space == 1 && curr->str[0] != 32)
			sh->cmd_table[++(*i)] = ft_strjoin_free(ft_strdup(curr->str), "\1");
		else
			sh->cmd_table[++(*i)] = ft_strdup(curr->str);
		sh->check = 1;
	}
	else if (check_word_token(curr->token) && sh->check == 1)
	{
		concat_right_helper(sh, curr, i);
	}
}
