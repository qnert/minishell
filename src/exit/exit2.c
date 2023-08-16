/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:45:40 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/16 10:46:28 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_exit_code_string(t_shell *sh, char *str)
{
	int		i;
	char	*tmp;
	char	*status;
	char	*res;

	i = 2;
	status = ft_itoa(sh->status);
	if (!str[i])
		return (status);
	while (str[i] && str[i] != '$')
		i++;
	tmp = ft_substr(str, 2, i - 2);
	res = ft_strjoin_free(status, tmp);
	free(tmp);
	return (res);
}
