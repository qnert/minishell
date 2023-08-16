/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:17:21 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/16 10:29:56 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_outfile_check(char *filepath)
{
	int	fd;
	int	fd_err;

	if (access(filepath, F_OK) == 0)
	{
		if (access(filepath, W_OK) == -1)
		{
			perror("Error");
			return (-1);
		}
	}
	fd = open(filepath, O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		fd_err = open(filepath, O_RDWR | O_CREAT, 0644);
		return (fd_err);
	}
	return (fd);
}

int	outfile_check_app(char *filepath)
{
	int	fd;
	int	fd_err;

	if (access(filepath, F_OK) == 0)
	{
		if (access(filepath, W_OK) == -1)
		{
			perror("Error");
			return (-1);
		}
	}
	fd = open(filepath, O_RDWR | O_APPEND);
	if (fd < 0)
	{
		fd_err = open(filepath, O_RDWR | O_CREAT, 0644);
		return (fd_err);
	}
	return (fd);
}

int	ft_infile_check(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDWR);
	if (fd < 0)
		return (perror("Error"), -1);
	return (fd);
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

bool	check_file_token(int token)
{
	if (token == 2 || token == 3)
		return (true);
	if (token == 4 || token == 5)
		return (true);
	return (false);
}
