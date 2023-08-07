/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:46:16 by skunert           #+#    #+#             */
/*   Updated: 2023/08/07 15:49:08 by skunert          ###   ########.fr       */
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
	if ((str[i] == '\0' && str[i] != '=') || str[i - 1] == '?')
	{
		if (ft_isalpha(str[i - 1]) && str[i] == '\0')
			return (true);
		write(2, " not a valid identifier\n", 24);
		sh->status = 1;
		return (true);
	}
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
	free_lst_files(sh->infiles);
	sh->infiles = NULL;
	free_lst_files(sh->outfiles);
	sh->outfiles = NULL;
	sh->pipes = 0;
	free_arr(sh->cmd_table);
	free_arr(sh->path_to_file_table);
	sh->path_to_file_table = NULL;
	sh->cmd_table = NULL;
	sh->check = 0;
}
