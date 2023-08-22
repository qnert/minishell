/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:46:16 by skunert           #+#    #+#             */
/*   Updated: 2023/08/22 17:59:09 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell	*shell_init(char **envp)
{
	t_shell	*sh;

	sh = malloc(sizeof(t_shell));
	sh->check = 0;
	sh->pipes = 0;
	sh->status = 0;
	sh->exit_code = 0;
	sh->infiles = NULL;
	sh->outfiles = NULL;
	sh->sterr = NULL;
	sh->envp = cpy_envp(envp);
	sh->cmd_table = NULL;
	sh->token_list = NULL;
	sh->path_to_file_table = NULL;
	return (sh);
}

int	get_len_matrix(char **matrix)
{
	int	len;

	len = 0;
	if (!matrix || !matrix[0])
		return (0);
	while (matrix && matrix[len] != NULL)
		len++;
	return (len);
}

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

void	terminate_struct(t_shell *sh)
{
	free_lst_lexer(sh->token_list);
	sh->token_list = NULL;
	free_lst_files(sh->infiles);
	sh->infiles = NULL;
	free_lst_files(sh->outfiles);
	sh->outfiles = NULL;
	sh->pipes = 0;
	if (sh->cmd_table && sh->cmd_table[0])
		free_arr(sh->cmd_table);
	if (sh->cmd_table && sh->cmd_table[0])
		free_arr(sh->path_to_file_table);
	sh->path_to_file_table = NULL;
	sh->cmd_table = NULL;
	sh->check = 0;
}

void	free_arr(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
