/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:10:38 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/21 15:18:32 by njantsch         ###   ########.fr       */
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

bool	parser_main(t_shell *sh)
{
	if (sh->token_list == NULL)
		return (true);
	if (check_list(sh) == false)
		return (false);
	return (true);
}
