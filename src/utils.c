/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:46:16 by skunert           #+#    #+#             */
/*   Updated: 2023/07/24 18:46:59 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	*shell_init(char **envp)
{
	t_shell	*sh;

	sh = malloc(sizeof(t_shell));
	sh->check = 0;
	sh->pipes = 0;
	sh->status = 0;
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
	while (matrix[len] != NULL)
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

bool	check_existence_env(t_shell *sh, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (printf("wrong args\n"), true);
	tmp = ft_substr(str, 0, i);
	i = 0;
	while (sh->envp[i] && ft_strncmp(sh->envp[i], tmp, ft_strlen(tmp)))
		i++;
	if (sh->envp[i] == NULL)
		return (false);
	free(sh->envp[i]);
	sh->envp[i] = ft_strdup(str);
	return (true);
}

void	terminate_struct(t_shell *sh)
{
	free_lst_lexer(sh->token_list);
	sh->token_list = NULL;
	printf("before infiles\n");
	if (sh->infiles != NULL)
		free_lst_files(sh->infiles);
	sh->infiles = NULL;
	printf("before outfiles\n");
	if (sh->outfiles != NULL)
		free_lst_files(sh->outfiles);
	sh->outfiles = NULL;
	printf("after outfiles\n");
	sh->pipes = 0;
	free_arr(sh->cmd_table);
	sh->cmd_table = NULL;
	sh->check = 0;
}
