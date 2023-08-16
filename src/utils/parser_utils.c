/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:05:49 by skunert           #+#    #+#             */
/*   Updated: 2023/08/16 17:11:38 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expander_helper(t_shell *sh, t_lexer *curr)
{
	int	tmp;

	tmp = 0;
	if (curr->token == 0 && curr->str[0] == '$' && curr->str[1] == '\0'
		&& (curr->next && (curr->next->token == 7
				|| curr->next->token == 6)))
	{
		free(curr->str);
		curr->str = ft_strdup("");
	}
	else
	{
		tmp = count_spaces(curr->str);
		get_expand(sh, curr);
		if (!ft_strchr(curr->str, '$'))
			replace_space_char(curr->str, tmp);
	}
}

void	get_expand_helper(char *first_str, t_lexer *curr, int i)
{
	if (curr->str[i] != '\0')
		first_str = ft_strjoin_free(first_str, &curr->str[i]);
	free(curr->str);
	curr->str = first_str;
}
