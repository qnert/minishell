/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:46:16 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 12:53:12 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	*shell_init(char **envp)
{
	t_shell	*sh;

	sh = malloc(sizeof(t_shell));
	sh->fd_in = -2;
	sh->fd_out = -2;
	sh->infile = NULL;
	sh->outfile = NULL;
	sh->sterr = NULL;
	sh->envp = cpy_envp(envp);
	sh->cmd_table = NULL;
	return (sh);
}

int	get_len_matrix(char **matrix)
{
	int	len;

	len = 0;
	while (matrix[len] != NULL)
		len++;
	return (len);
}
