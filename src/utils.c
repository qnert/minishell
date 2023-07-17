/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:46:16 by skunert           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/17 13:40:57 by njantsch         ###   ########.fr       */
=======
/*   Updated: 2023/07/17 14:09:12 by skunert          ###   ########.fr       */
>>>>>>> 84000c90ff3ed8e479c384c5981982ca46aa38f3
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cpy_envp(char **envp)
{
	int		i;
	char	*str;
	char	**envp_cpy;

	i = 0;
	envp_cpy = ft_calloc(get_len_matrix(envp), sizeof(char *));
	while (envp[i] != NULL)
	{
		str = get_envp_name(envp[i]);
		envp_cpy[i] = getenv(str);
		str = ft_strjoin_free(str, "=");
		envp_cpy[i] = ft_strjoin_free(str, envp_cpy[i]);
		i++;
	}
	return (envp_cpy);
}

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
