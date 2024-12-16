/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:40:01 by mfrancis          #+#    #+#             */
/*   Updated: 2024/10/23 13:00:10 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 130;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	here_handler(int signal)
{
	if(signal == SIGINT)
	{
		g_signal = 130;
		ft_putchar_fd('\n', 1);
		close(STDIN_FILENO);
	}
}

void	setup_signals(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sigemptyset(&sig_quit.sa_mask);
	sig_int.sa_handler = sig_handler;
	sig_quit.sa_handler = SIG_IGN;
	sig_int.sa_flags = SA_RESTART;
	sig_quit.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	stop_signals(void)
{
	struct sigaction	sig_ignore;

	sigemptyset(&sig_ignore.sa_mask);
	sig_ignore.sa_handler = SIG_IGN;
	sig_ignore.sa_flags = 0;
	sigaction(SIGINT, &sig_ignore, NULL);
	sigaction(SIGQUIT, &sig_ignore, NULL);
}

void	setup_signals_here(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sigemptyset(&sig_quit.sa_mask);
	sig_int.sa_handler = here_handler;
	sig_quit.sa_handler = SIG_IGN;
	sig_int.sa_flags = SA_RESTART;
	sig_quit.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}

