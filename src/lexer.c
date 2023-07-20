/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:55:39 by skunert           #+#    #+#             */
/*   Updated: 2023/07/20 16:14:47 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_null(char *str, int i)
{
	if (str[i] == '\0')
		return (true);
	return (false);
}

void	check_pipe(t_shell *sh, char *str, int i)
{
	if (str[i] == '|')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup("|");
			sh->token_list->token = PIPE;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, "|", PIPE);
	}
}

void	check_redirect_plus(t_shell *sh, char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup("<<");
			sh->token_list->token = LESS_LESS;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, "<<", LESS_LESS);
	}
	if (str[i] == '>' && str[i + 1] == '>')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup(">>");
			sh->token_list->token = GREAT_GREAT;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, ">>", GREAT_GREAT);
	}
}

void	check_redirect(t_shell *sh, char *str, int i)
{
	if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup("<");
			sh->token_list->token = LESS;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, "<", LESS);
	}
	if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
	{
		if (sh->token_list == NULL)
		{
			sh->token_list = malloc(sizeof(t_lexer));
			sh->token_list->str = ft_strdup(">");
			sh->token_list->token = GREAT;
			sh->token_list->next = NULL;
		}
		else
			lst_add_new(sh->token_list, ">", GREAT);
	}
	check_redirect_plus(sh, str, i);
}

void	lexer(t_shell *sh, char *str)
{
	int	i;

	i = 0;
	while (1)
	{
		if (check_null(str, i) == true)
			break ;
		check_pipe(sh, str, i);
		check_redirect(sh, str, i);
		i++;
	}
}
