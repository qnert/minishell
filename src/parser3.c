/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:27:58 by skunert           #+#    #+#             */
/*   Updated: 2023/07/25 12:28:07 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander(t_shell *sh)
{
	t_lexer	*curr;

	curr = sh->token_list;
	while (curr)
	{
		if (ft_strchr(curr->str, '$') != 0)
			get_expand(sh, curr->str, curr);
		curr = curr->next;
	}
}

void	read_till_limiter(t_files *curr)
{
	char	*line;

	printf("Eingabe erreicht\n");
	printf("file descirptor: %d\n", curr->fd);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, curr->delim, ft_strlen(curr->delim)) != 0)
	{
		ft_putstr_fd(line, curr->fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	printf("read finished\n");
	printf("file descirptor: %d\n", curr->fd);
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