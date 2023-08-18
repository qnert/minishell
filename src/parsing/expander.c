/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:21:03 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/18 17:07:49 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_spaces(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == 32)
			counter++;
		i++;
	}
	return (counter);
}

void	expander(t_shell *sh)
{
	t_lexer	*curr;

	curr = sh->token_list;
	while (curr)
	{
		if (ft_strncmp(curr->str, "unset", 5) == 0)
		{
			if (curr->next)
				curr = curr->next->next;
			if (curr == NULL)
				return ;
		}
		if (ft_strchr(curr->str, '~') != 0)
			expand_to_home(sh, curr);
		if ((curr->token == 0 || curr->token == 7)
			&& ft_strchr(curr->str, '$') != 0)
			expander_helper(sh, curr);
		curr = curr->next;
	}
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
		while (curr->str[i] && curr->str[i] != ' ' && curr->str[i] != '$'
			&& curr->str[i] != '\'' && curr->str[i] != '/')
			i++;
		if (curr->str[i - 1] == '?' && curr->str[i - 2] != '$')
			i--;
		env_var = change_str_to_env(sh, ft_substr(curr->str, start, i - start));
		first_str = ft_strjoin_free(first_str, env_var);
		free(env_var);
	}
	get_expand_helper(first_str, curr, i);
}

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

void	expand_to_home(t_shell *sh, t_lexer *curr)
{
	int		i;
	int		check;
	char	*tmp;

	i = 0;
	check = 0;
	tmp = NULL;
	while (curr->str[i])
	{
		if ((curr->str[i] == '~' && ft_strlen(curr->str) == 1
			&& !curr->str[i - 1])
			|| (curr->str[i] == '~' && curr->str[i + 1] == '/'
			&& !curr->str[i - 1]))
			check = 1;
		i++;
	}
	if (check == 0)
		return ;
	tmp = get_home_from_env(sh);
	tmp = ft_strjoin_free(tmp, curr->str + 1);
	curr->str = tmp;
}
