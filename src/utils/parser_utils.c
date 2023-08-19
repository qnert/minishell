/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:05:49 by skunert           #+#    #+#             */
/*   Updated: 2023/08/19 21:00:20 by skunert          ###   ########.fr       */
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

void	table_init_helper(t_shell *sh, t_lexer *curr, int *i)
{
	if (curr->next && check_file_token(curr->next->token)
		&& curr->next->next && sh->check == 1 && curr->next->next->next)
		sh->cmd_table[*i] = ft_strjoin_free(sh->cmd_table[*i], "\1");
	if (sh->check == 0 && curr->next
		&& (curr->next->token == 2 || curr->next->token == 3)
		&& curr->next->next && !curr->next->next->next)
		sh->cmd_table[++(*i)] = ft_strdup("\1");
}

char	*right_here_doc_name(t_files *lst, char *str, int x)
{
	int		i;
	char	*tmp;
	char	*ret_str;
	t_files	*curr;

	i = 0;
	tmp = NULL;
	curr = lst;
	while (curr->next && x == 1)
	{
		if (lst->delim != NULL)
			i++;
		curr = curr->next;
	}
	tmp = ft_itoa(i);
	ret_str = ft_strjoin(str, tmp);
	free(tmp);
	return (ret_str);
}

void	get_here_doc_helper(t_shell *sh, t_lexer *curr, int pipe)
{
	if (sh->infiles == NULL)
	{
		sh->infiles = malloc(sizeof(t_files));
		if (curr->next->token == SINGLE || curr->next->token == DOUBLE
			|| (curr->next->next && curr->next->next->token == SINGLE
			&& ft_strlen(curr->next->next->str) == 0)
			|| (curr->next->next && curr->next->next->token == DOUBLE
			&& ft_strlen(curr->next->next->str) == 0))
			sh->infiles->file_name
				= right_here_doc_name(sh->infiles, "here_docc", 0);
		else
			sh->infiles->file_name
				= right_here_doc_name(sh->infiles, "here_doc", 0);
		if ((curr->next->token == SINGLE
			&& ft_strlen(curr->next->str) == 0 && curr->next->next)
			|| (curr->next->token == DOUBLE
			&& ft_strlen(curr->next->str) == 0 && curr->next->next))
			sh->infiles->delim = ft_strdup(curr->next->next->str);
		else
			sh->infiles->delim = ft_strdup(curr->next->str);
		sh->infiles->fd = ft_outfile_check(sh->infiles->file_name);
		sh->infiles->pos = pipe;
		sh->infiles->next = NULL;
	}
	else
		lst_add_new_here_doc(sh->infiles, curr, pipe);
}
