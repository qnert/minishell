/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:37:38 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/21 23:45:24 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_hd_name(t_shell *sh, t_lexer *curr, int pipe)
{
	if ((curr->next->token == SINGLE
			&& ft_strlen(curr->next->str) == 0 && curr->next->next)
		|| (curr->next->token == DOUBLE
			&& ft_strlen(curr->next->str) == 0 && curr->next->next))
		sh->infiles->delim = ft_strdup(curr->next->next->str);
	else
		sh->infiles->delim = ft_strdup(curr->next->str);
	sh->infiles->fd = ft_outfile_check(sh->infiles->file_name);
	sh->infiles->pos = pipe;
	sh->infiles->next = NULL;
}

void	concat_right_helper2(t_shell *sh, t_lexer *curr, int *i)
{
	if ((curr->token == 6 || curr->token == 7) && curr->next != NULL
		&& curr->b_space == 1 && curr->f_space == 0
		&& ft_strlen(curr->str) != 0 && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free
			(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
	else if ((curr->token == 6 || curr->token == 7) && curr->next != NULL
		&& curr->b_space == 1 && curr->f_space == 1
		&& sh->cmd_table[(*i)][ft_strlen(sh->cmd_table[(*i)]) - 1] == '\1'
		&& sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free
			(ft_strjoin_free(sh->cmd_table[(*i)], curr->str), "\1");
	else if ((curr->token == 6 || curr->token == 7) && curr->next != NULL
		&& curr->b_space == 1 && curr->f_space == 1 && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free(ft_strjoin_free
				(ft_strjoin_free(sh->cmd_table[(*i)], "\1"), curr->str), "\1");
	else if (check_word_token(curr->token)
		&& (curr->next != NULL) && sh->check == 1)
		sh->cmd_table[(*i)] = ft_strjoin_free(sh->cmd_table[(*i)], curr->str);
}

void	rtl_loop(t_shell *sh, t_files *curr, char *line)
{
	while (line != NULL && g_cntrlc == false)
	{
		if (ft_strncmp(line, curr->delim, ft_strlen(curr->delim)) == 0
			&& (ft_strlen(line) - 1) == ft_strlen(curr->delim))
			break ;
		if (ft_strncmp(curr->file_name, "here_docc", 9) != 0)
			line = get_expand_here_doc(sh, line);
		if (ft_strlen(line) == 0)
		{
			free(line);
			line = ft_strdup("\n");
		}
		ft_putstr_fd(line, curr->fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
}
