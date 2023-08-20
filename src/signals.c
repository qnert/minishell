/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:36:19 by skunert           #+#    #+#             */
/*   Updated: 2023/08/20 18:20:48 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_cchars(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) != 0)
		perror("minishell: tcgetattr");
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &term) != 0)
		perror("minishell: tcsetattr");
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signals(void)
{
	struct sigaction	int_sig;

	if (isatty(0))
		handle_cchars();
	int_sig.sa_handler = &sig_handler;
	sigaction(SIGINT, &int_sig, NULL);
	signal(SIGQUIT, SIG_IGN);
}
