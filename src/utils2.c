/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:21:29 by skunert           #+#    #+#             */
/*   Updated: 2023/08/13 12:45:02 by skunert          ###   ########.fr       */
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

char	*change_str_to_env(t_shell *sh, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strchr(str, '$') == 0)
		return (str);
	if (str[i] == '$' && str[i + 1] == '?')
		return (get_exit_code_string(sh, str));
	if (ft_strlen(str) == 1 && str[i] == '$')
		return (str);
	if (ft_strlen(str) == 1 && !ft_isalnum(str[i]))
		return (str);
	str = ft_strjoin_free(str, "=");
	while (sh->envp && sh->envp[i]
		&& ft_strncmp(sh->envp[i], str + 1, ft_strlen(str) - 1) != 0)
		i++;
	if (!sh->envp || !sh->envp[i])
		return (free(str), ft_strdup(""));
	while (sh->envp[i][j] != '=')
		j++;
	free(str);
	return (ft_substr(sh->envp[i], j + 1, ft_strlen(sh->envp[i]) - j + 1));
}

void	get_expand(t_shell *sh, t_lexer *curr)
{
	int		i;
	int		start;
	char	*first_str;
	char	*env_var;

	i = 0;
	while (curr->str[i] && curr->str[i] != '$')
		i++;
	if (i > 0)
		first_str = ft_substr(curr->str, 0, i);
	else
		first_str = ft_strdup("");
	while (curr->str[i] && ft_strchr(curr->str + i, '$') != 0)
	{
		start = i++;
		while (curr->str[i] && curr->str[i] != '=')
			i++;
		env_var = change_str_to_env(sh, ft_substr(curr->str, start, i - start));
		first_str = ft_strjoin_free(first_str, env_var);
		free(env_var);
	}
	if (curr->str[i] != '\0')
		first_str = ft_strjoin_free(first_str, &curr->str[i]);
	free(curr->str);
	curr->str = first_str;
}
