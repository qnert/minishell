/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:27:58 by skunert           #+#    #+#             */
/*   Updated: 2023/08/09 16:32:37 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander(t_shell *sh)
{
	t_lexer	*curr;

	curr = sh->token_list;
	while (curr)
	{
		if (ft_strncmp(curr->str, "unset", 5) == 0)
		{
			if (curr->next)
				curr = curr->next->next;
			if (curr == NULL)
				return ;
		}
		if ((curr->token == 0 || curr->token == 7)
			&& ft_strchr(curr->str, '$') != 0)
		{
			if (curr->str[0] == '$' && curr->str[1] == '\0'
				&& (curr->next && curr->next->token == 7))
			{
				free(curr->str);
				curr->str = ft_strdup("");
			}
			else
				get_expand(sh, curr);
		}
		curr = curr->next;
	}
}

void	read_till_limiter(t_shell *sh, t_files *curr)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line != NULL && ft_strncmp(line, curr->delim,
			ft_strlen(curr->delim)) != 0)
	{
		line = get_expand_here_doc(sh, line);
		ft_putstr_fd(line, curr->fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(curr->fd);
	curr->fd = open(curr->file_name, O_RDONLY);
	unlink("here_doc");
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

t_lexer	*check_correct_file(t_lexer *lst)
{
	t_lexer	*curr;
	int		word_count;
	int		infile_count;

	curr = lst;
	word_count = 0;
	infile_count = 0;
	while (curr)
	{
		if (curr->token == LESS)
			infile_count++;
		if (check_word_token(curr->token))
			word_count++;
		curr = curr->next;
	}
	if (infile_count == word_count)
		return (NULL);
	curr = lst;
	if (curr->token > 1 && curr->token < 6 && !curr->next->next)
		return (NULL);
	while (curr->token > 1 && curr->token < 6 && curr->next->next)
		curr = curr->next->next;
	if (curr->token > 1 && curr->token < 6 && !curr->next->next)
		return (NULL);
	return (curr);
}
