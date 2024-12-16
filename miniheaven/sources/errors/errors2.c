/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:08:09 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/16 17:26:32 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	free_exit(t_minishell *minishell, char *str)
{
	if (minishell->local)
	{
		free_array(minishell->local);
		minishell->local = NULL;
	}
	if (str && str[0] != '\0')
		ft_putstr_fd(str, 2);
	if (minishell->envp)
		free_array(minishell->envp);
	if (minishell->temp_stdin != -1)
		close (minishell->temp_stdin);
	if (minishell->temp_stdout != -1)
		close (minishell->temp_stdout);
	if (minishell->_pipe_ == 1)
	{
		close(minishell->fd[0]);
		close(minishell->fd[1]);
	}
	if (minishell->fd[1] > 0)
		close(1);
	if (minishell->fd[0] > 0)
		close(0);
	if (minishell->cmd)
	{
		free(minishell->cmd);
		minishell->cmd = NULL;
	}
	if (minishell->infile != -1)
		close(minishell->infile);
	if (minishell->temp_stdin != -1)
		close(0);
	if (minishell->temp_stdout != -1)
		close(1);
	free_utils(minishell);
	fd_clean();
	exit(g_signal);
} */

void	close_pipe(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	free_pointer(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
