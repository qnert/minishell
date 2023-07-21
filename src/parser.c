/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:10:38 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/21 16:57:11 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_list(t_shell *sh)
{
	t_lexer	*curr;
	int		pipe;

	pipe = 0;
	curr = sh->token_list;
	while (curr)
	{
		if (sh->token_list->token == 1)
			return (false);
		if (curr->next == NULL && curr->token > 0 && curr->token < 6)
			return (false);
		if (curr->token == 1)
			pipe++;
		if ((curr->token == 4 || curr->token == 5) && pipe != 0)
			return (false);
		if (curr->next && curr->token > 0 && curr->token < 6
			&& curr->token == curr->next->token)
			return (false);
		curr = curr->next;
	}
	return (true);
}

void	get_in_out_file(t_shell *sh)
{
	t_lexer	*curr;

	curr = sh->token_list;
	while (curr)
	{
		if (curr->token == 4)
			sh->infile = ft_strdup(curr->next->str);
		if (curr->token == 5)
		{
			sh->infile = ft_strdup("here_doc");
			sh->here_doc_delim = ft_strdup(curr->next->str);
		}
		curr = curr->next;
	}
}

bool	parser_main(t_shell *sh)
{
	if (sh->token_list == NULL)
		return (true);
	if (check_list(sh) == false)
		return (false);
	get_in_out_file(sh);
	return (true);
}
