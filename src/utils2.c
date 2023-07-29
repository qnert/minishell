/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:21:29 by skunert           #+#    #+#             */
/*   Updated: 2023/07/27 15:47:55 by skunert          ###   ########.fr       */
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

void	change_str_to_env(t_shell *sh, char *str, t_lexer *curr)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (sh->envp && sh->envp[i]
		&& strncmp(sh->envp[i], str, ft_strlen(str)) != 0)
		i++;
	if (sh->envp[i] == NULL)
	{
		free(curr->str);
		curr->str = ft_strdup("");
		return ;
	}
	while (sh->envp && sh->envp[i] && sh->envp[i][j] != '=')
		j++;
	j++;
	start = j;
	free(curr->str);
	curr->str = ft_substr(sh->envp[i], start, ft_strlen(sh->envp[i]) - start);
}

void	get_expand(t_shell *sh, char *tmp, t_lexer *curr)
{
	int		i;
	int		j;
	char	*ret_str;

	i = 0;
	j = 0;
	while (tmp[i] && tmp[i] != '$')
		i++;
	if (tmp[i] == '$' && tmp[i + 1] == '\0')
		return ;
	while (tmp[i + j] && (tmp[i + j] != 32
			|| (tmp[i + j] >= 9 && tmp[i + j] <= 13)))
		j++;
	ret_str = ft_substr(tmp, i + 1, j);
	ret_str = ft_strjoin_free(ret_str, "=");
	change_str_to_env(sh, ret_str, curr);
	free(ret_str);
	return ;
}
