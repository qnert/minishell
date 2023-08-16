/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:49:35 by skunert           #+#    #+#             */
/*   Updated: 2023/08/16 11:02:05 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	replace_split_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 1)
			str[i] = 32;
		i++;
	}
}

char	*ft_charjoin_free(char *str, char c)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	while (str[++i])
		tmp[i] = str[i];
	tmp[i] = c;
	tmp[++i] = '\0';
	free(str);
	return (tmp);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	change_f_b_spaces(t_lexer *lst, char *str, int i, int start)
{
	t_lexer	*curr;

	curr = lst;
	while(curr->next)
		curr = curr->next;
	if (str[start - 2] && str[start - 2] == ' ')
		curr->f_space = 1;
	if (str[i + 1] && str[i + 1] == ' ')
		curr->b_space = 1;
}

void	replace_space_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
			str[i] = 1;
		i++;
	}
}
