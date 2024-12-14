/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 00:37:59 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/10 10:21:59 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_handler(int signal)
{
	if (signal == SIGQUIT)
		g_signal = 131;
	if (signal == SIGINT)
		g_signal = 130;
}

void	setup_signals_executer(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sigemptyset(&sig_quit.sa_mask);
	sig_int.sa_handler = exec_handler;
	sig_quit.sa_handler = exec_handler;
	sig_int.sa_flags = SA_RESTART;
	sig_quit.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
// exit status:
// 0 
// 130 - 
// 131
// 127 - nao foi