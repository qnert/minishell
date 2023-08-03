/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:12:45 by skunert           #+#    #+#             */
/*   Updated: 2023/08/03 13:24:27 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_expand_here_doc(t_shell *sh, char *str)
{
	int		i;
	int		start;
	char	*first_str;
	char	*env_var;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i > 0)
		first_str = ft_substr(str, 0, i);
	else
		first_str = ft_strdup("");
	while (str[i] && ft_strchr(str + i, '$') != 0)
	{
		start = i;
		while (str[++i] && ft_isalnum(str[i]))
			i++;
		env_var = change_str_to_env(sh, ft_substr(str, start, i - start));
		first_str = ft_strjoin_free(first_str, env_var);
		free(env_var);
	}
	if (str[i] != '\0')
		first_str = ft_strjoin_free(first_str, &str[i]);
	free(str);
	return (first_str);
}

void	exit_status(t_shell *sh, char **tmp, int status)
{
	terminate_struct(sh);
	free_arr(tmp);
	free_arr(sh->envp);
	free(sh);
	exit(status);
}

void	go_to_home(t_shell *sh)
{
	char	*tmp;

	tmp = get_home_from_env(sh);
	if (!tmp)
		return ((void)write(2, "miniHell: cd: HOME not set\n", 27));
	if (chdir(tmp) != 0)
	{
		free(tmp);
		perror("cd");
	}
}
