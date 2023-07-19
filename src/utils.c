/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:46:16 by skunert           #+#    #+#             */
/*   Updated: 2023/07/19 12:27:07 by njantsch         ###   ########.fr       */
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

void	terminate_struct(t_shell *sh)
{
	if (sh->pipes > 0)
		free(sh->pipes_location);
	if (sh->ands > 0)
		free(sh->ands_location);
	if (sh->ors > 0)
		free(sh->ors_location);
	free_arr(sh->path_to_file_table);
	free_arr(sh->cmd_table);
}

void	print_marix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

bool	check_existence_env(t_shell *sh, char *str)
{
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (printf("wrong args\n"), true);
	tmp = ft_substr(str, 0, i);
	start = i + 1;
	i = 0;
	while (sh->envp[i] && ft_strncmp(sh->envp[i], tmp, ft_strlen(tmp)))
		i++;
	if (sh->envp[i] == NULL)
		return (false);
	free(sh->envp[i]);
	sh->envp[i] = ft_strdup(str);
	return (true);
}
