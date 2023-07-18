/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:12:41 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 14:27:33 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirect_in(t_shell *sh)
{
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	start = 0;
	while (sh->cmd_table[0][i] != '\0')
	{
		if (sh->cmd_table[0][i] == '<')
			i++;
		else
			break ;
		while (sh->cmd_table[0][i] == 32 || sh->cmd_table [0][i] == 9)
			i++;
		start = i;
		while (ft_isalnum(sh->cmd_table[0][i++]))
		sh->infile = ft_substr(sh->cmd_table[0], start, i - start);
		while (sh->cmd_table[0][i] == 32 || sh->cmd_table [0][i] == 9)
			i++;
		tmp = ft_substr(sh->cmd_table[0], i,
				ft_strlen(sh->cmd_table[0]) - i + 1);
		free(sh->cmd_table[0]);
		sh->cmd_table[0] = ft_strdup(tmp);
		free(tmp);
	}
}

void	ft_trim_table(t_shell *sh, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (sh->cmd_table[len][i] && sh->cmd_table[len][i] != '>')
		i++;
	while (sh->cmd_table[len][i] == 32 || sh->cmd_table[len][i] == 9)
		i--;
	tmp = ft_substr(sh->cmd_table[len], 0, i);
	free(sh->cmd_table[len]);
	sh->cmd_table[len] = ft_strdup(tmp);
	free(tmp);
}

void	check_redirect_out(t_shell *sh)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = get_len_matrix(sh->cmd_table) - 1;
	while (sh->cmd_table[len][i])
	{
		while (sh->cmd_table[len][i] && sh->cmd_table[len][i] != '>')
			i++;
		if (sh->cmd_table[len][i] == '\0')
			break ;
		i++;
		while (sh->cmd_table[len][i] == 32 || sh->cmd_table[len][i] == 9)
			i++;
		start = i;
		sh->outfile = ft_substr(sh->cmd_table[len], start,
				ft_strlen(sh->cmd_table[len]) - 1);
		ft_trim_table(sh, len);
	}
}

int	count_args(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			counter++;
		i++;
	}
	return (counter);
}

int	parser_main(char *str, t_shell *sh)
{
	int		i;
	char	**tmp;

	i = 0;
	sh->cmd_table = malloc(sizeof(char *) * count_args(str) + 1);
	if (!sh->cmd_table)
		return (1);
	sh->path_to_file_table = malloc(sizeof(char *) * count_args(str) + 1);
	if (!sh->path_to_file_table)
		return (free(sh->cmd_table), 1);
	tmp = ft_split(str, '|');
	while (tmp[i] != NULL)
	{
		sh->cmd_table[i] = ft_strtrim(tmp[i], " ");
		i++;
	}
	sh->cmd_table[i] = NULL;
	free_arr(tmp);
	check_redirect_in(sh);
	check_redirect_out(sh);
	i = 0;
	while (sh->cmd_table[i])
	{
		// printf("%s command    %d  i\n", sh->cmd_table[i], i);
		if (access_check(sh, sh->cmd_table[i]) == 1)
			perror("");
		else
			printf("%s\n", sh->path_to_file_table[i]);
		i++;
	}
	return (1);
}
