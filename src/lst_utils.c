/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:19:39 by skunert           #+#    #+#             */
/*   Updated: 2023/07/20 15:10:23 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_add_new(t_lexer *lst, char *str, int token)
{
	t_lexer	*curr;
	t_lexer	*new_node;

	curr = lst;
	new_node = malloc(sizeof(t_lexer));
	if (new_node == NULL)
		return (-1);
	new_node->str = ft_strdup(str);
	new_node->token = token;
	new_node->next = NULL;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
	return (1);
}

void	free_lst(t_lexer *lst)
{
	t_lexer	*curr;
	t_lexer	*tmp;

	curr = lst;
	while (curr != NULL)
	{
		free(curr->str);
		curr->str = NULL;
		curr = curr->next;
	}
	curr = lst;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}
