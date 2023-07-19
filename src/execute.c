/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:55:34 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 15:29:34 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_cmd(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->cmd_table[i])
	{
		if (check_build_in(sh->cmd_table[i]) == true)
			handle_build_in(sh, sh->cmd_table[i]);
		i++;
	}
	return (1);
}
