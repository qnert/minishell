/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:21:29 by skunert           #+#    #+#             */
/*   Updated: 2023/07/22 18:05:22 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_outfile_append_check(char *filepath)
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
	fd = open(filepath, O_RDWR | O_APPEND, 0644);
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
