/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:27:58 by skunert           #+#    #+#             */
/*   Updated: 2023/07/25 18:01:42 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander(t_shell *sh)
{
	t_lexer	*curr;

	curr = sh->token_list;
	while (curr)
	{
		if ((curr->token == 0 || curr->token == 7)
			&& ft_strchr(curr->str, '$') != 0)
			get_expand(sh, curr->str, curr);
		curr = curr->next;
	}
}

void	read_till_limiter(t_files *curr)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, curr->delim, ft_strlen(curr->delim)) != 0)
	{
		ft_putstr_fd(line, curr->fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(curr->fd);
	curr->fd = open(curr->file_name, O_RDONLY);
}

void	check_and_write_here_doc(t_files *infiles)
{
	t_files	*curr;

	curr = infiles;
	while (curr)
	{
		if (curr->delim != NULL)
			read_till_limiter(curr);
		curr = curr->next;
	}
}
