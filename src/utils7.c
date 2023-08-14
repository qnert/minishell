/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:44:58 by skunert           #+#    #+#             */
/*   Updated: 2023/08/14 15:01:55 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_exit_code(t_shell *sh)
{
	int	status;

	status = 0;
	if (WIFEXITED(sh->status))
		status = WEXITSTATUS(sh->status);
	if (WIFSIGNALED(sh->status))
		status = WTERMSIG(sh->status);
	return (status);
}
