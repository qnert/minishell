/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:10:38 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/22 17:44:23 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	table_init(t_shell *sh)
{
	t_lexer	*curr;
	int		i;

	i = -1;
	curr = sh->token_list;
	sh->cmd_table = malloc(sizeof(char *) * (sh->pipes + 2));
	while (curr)
	{
		if (curr->token == 1)
			sh->check = 0;
		if (curr->token > 1 && curr->token < 6)
			curr = curr->next->next;
		if (!curr)
			break ;
		if (curr->token == 0 && sh->check == 0)
		{
			sh->cmd_table[++i] = ft_strdup(curr->str);
			sh->check = 1;
		}
		else if (curr->token == 0 && sh->check == 1)
			sh->cmd_table[i] = ft_strjoin_free(
					ft_strjoin(sh->cmd_table[i], " "), curr->str);
		curr = curr->next;
	}
	sh->cmd_table[++i] = NULL;
}

bool	check_list(t_shell *sh)
{
	t_lexer	*curr;

	curr = sh->token_list;
	while (curr)
	{
		if (sh->token_list->token == 1)
			return (false);
		if (curr->next == NULL && curr->token > 0 && curr->token < 6)
			return (false);
		if (curr->next && curr->token > 0 && curr->token < 6
			&& curr->token == curr->next->token)
			return (false);
		if (curr->next && curr->token > 3 && curr->token < 6
			&& (curr->token - 1 == curr->next->token
				|| curr->token == curr->next->token - 1))
			return (false);
		if (curr->next && curr->token > 1 && curr->token < 4
			&& (curr->token - 1 == curr->next->token
				|| curr->token == curr->next->token - 1))
			return (false);
		if (curr->token > 1 && curr->token < 6 && curr->next->token == 1)
			return (false);
		curr = curr->next;
	}
	return (true);
}

void	get_infile(t_shell *sh)
{
	t_lexer	*curr;

	curr = sh->token_list;
	while (curr)
	{
		if (curr->token == PIPE)
			sh->pipes++;
		if (curr->token == 4)
		{
			if (sh->infiles == NULL)
			{
				sh->infiles = malloc(sizeof(t_files));
				sh->infiles->file_name = ft_strdup(curr->next->str);
				sh->infiles->delim = NULL;
				sh->infiles->fd = ft_infile_check(sh->infiles->file_name);
				sh->infiles->pos = sh->pipes;
				sh->infiles->next = NULL;
			}
			else
				lst_add_new_file(sh->infiles, curr->next->str,
					NULL, sh->pipes);
		}
		curr = curr->next;
	}
}

void	get_here_doc(t_shell *sh)
{
	int		pipe;
	t_lexer	*curr;

	pipe = 0;
	curr = sh->token_list;
	while (curr)
	{
		if (curr->token == PIPE)
			pipe++;
		if (curr->token == 5)
		{
			if (sh->infiles == NULL)
			{
				sh->infiles = malloc(sizeof(t_files));
				sh->infiles->file_name = ft_strdup("here_doc");
				sh->infiles->delim = ft_strdup(curr->next->str);
				sh->infiles->fd = ft_outfile_check(sh->infiles->file_name);
				sh->infiles->pos = pipe;
				sh->infiles->next = NULL;
			}
			else
				lst_add_new_file(sh->infiles, NULL, curr->next->str, pipe);
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
	get_infile(sh);
	get_outfile(sh);
	get_here_doc(sh);
	table_init(sh);
	return (true);
}