/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:12:07 by njantsch          #+#    #+#             */
/*   Updated: 2023/07/19 12:47:39 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**check_operands(t_shell *sh, char *str)
{
	int	i;

	i = 0;
	sh->pipes = 0;
	sh->ands = 0;
	sh->ors = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] != '|' && str[i - 1] != '|')
			sh->pipes++;
		else if (str[i] == '|' && str[i + 1] == '|' && str[i - 1] != '|')
			sh->ors++;
		else if (str[i] == '&' && str[i + 1] == '&' && str[i - 1] != '&')
			sh->ands++;
		i++;
	}
	if (sh->pipes > 0)
		sh->pipes_location = malloc(sizeof(int) * sh->pipes);
	if (sh->ands > 0)
		sh->ands_location = malloc(sizeof(int) * sh->ands);
	if (sh->ors > 0)
		sh->ors_location = malloc(sizeof(int) * sh->ors);
	get_operands_location(sh, str);
	return (split_commands(sh, str));
}

void	get_operands_location(t_shell *sh, char *str)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	which_cmd;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	which_cmd = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] != '|' && str[i - 1] != '|')
			sh->pipes_location[j++] = ++which_cmd;
		else if (str[i] == '|' && str[i + 1] == '|' && str[i - 1] != '|')
			sh->ors_location[k++] = ++which_cmd;
		else if (str[i] == '&' && str[i + 1] == '&' && str[i - 1] != '&')
			sh->ands_location[l++] = ++which_cmd;
		i++;
	}
}

char	**split_commands(t_shell *sh, char *str)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * count_args(str) + 1);
	if ((sh->pipes > 0 && sh->ands == 0) || (sh->ors > 0 && sh->ands == 0))
		return (ft_split(str, '|'));
	else if (sh->pipes == 0 && sh->ands > 0 && sh->ors == 0)
		return (ft_split(str, '&'));
	else if ((sh->pipes > 0 && sh->ands > 0) || (sh->ors > 0 && sh->ands > 0)
		|| (sh->pipes > 0 && sh->ands > 0 && sh->ors > 0))
		return (split_by_operators(str, new));
	else
	{
		new[i++] = ft_substr(str, 0, ft_strlen(str));
		new[i] = NULL;
		return (new);
	}
	return (NULL);
}

char	**split_by_operators(char *str, char **new)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	while (str[i])
	{
		if ((str[i] == '|' && str[i - 1] != '|') || (str[i] == '&'
				&& str[i + 1] == '&' && str[i - 1] != '&'))
		{
			new[j] = ft_substr(str, start, i - start);
			if (str[i + 1] == '|' || (str[i] == '&' && str[i + 1] == '&'))
				start = i + 2;
			else
				start = i + 1;
			j++;
		}
		i++;
	}
	new[j++] = ft_substr(str, start, i - start);
	new[j] = NULL;
	return (new);
}
