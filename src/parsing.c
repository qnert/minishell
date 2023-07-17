/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:12:09 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/17 15:43:25 by njantsch         ###   ########.fr       */
=======
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:12:41 by skunert           #+#    #+#             */
/*   Updated: 2023/07/17 15:34:34 by skunert          ###   ########.fr       */
>>>>>>> 84000c90ff3ed8e479c384c5981982ca46aa38f3
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD

=======
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
		while (sh->cmd_table[0][i] == 32
			|| sh->cmd_table [0][i] == 9)
			i++;
		start = i;
		while (sh->cmd_table[0][i + 1] != ' ')
			i++;
		sh->infile = ft_substr(sh->cmd_table[0], start, i - 1);
		tmp = ft_substr(sh->cmd_table[0], i + 2,
				ft_strlen(sh->cmd_table[0]) - 1);
		free(sh->cmd_table[0]);
		sh->cmd_table[0] = ft_strdup(tmp);
		free(tmp);
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
	tmp = ft_split(str, '|');
	while (tmp[i] != NULL)
	{
		sh->cmd_table[i] = ft_strtrim(tmp[i], " ");
		i++;
	}
	sh->cmd_table[i] = NULL;
	free_arr(tmp);
	check_redirect_in(sh);
	printf("%s\n", sh->infile);
	return (1);
}
>>>>>>> 84000c90ff3ed8e479c384c5981982ca46aa38f3
