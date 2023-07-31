/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:36:19 by skunert           #+#    #+#             */
/*   Updated: 2023/07/31 15:21:55 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	set_signals(void)
{
	struct sigaction	quit_sig;
	struct sigaction	int_sig;

	quit_sig.sa_handler = &sig_handler;
	int_sig.sa_handler = &sig_handler;
	sigaction(SIGQUIT, &quit_sig, NULL);
	sigaction(SIGINT, &int_sig, NULL);
}
