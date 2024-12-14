/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:00:58 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/10 19:10:39 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_utils(t_minishell *minishell)
{
	if (minishell->ast)
	{
		free_ast(minishell->ast);
		minishell->ast = NULL;
	}
	if (minishell->display)
	{
		free(minishell->display);
		minishell->display = NULL;
	}
	if (minishell->tokens)
		free_tokens(minishell);
	if (minishell->heredoc)
	{
		free_heredoc(minishell->heredoc);
		// free(minishell->heredoc);
		minishell->heredoc = NULL;
	}
	if (minishell->expander)
	{
		free_expand(minishell->expander);
		free(minishell->expander);
		minishell->expander = NULL;
    }
}

void	free_all(t_minishell *minishell, char *str)
{
	free_utils(minishell);
	if (str && str[0] != '\0')
		ft_putstr_fd(str, 2);
}

void	free_exit(t_minishell *minishell, char *str)
{
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
}

void	fd_clean(void)
{
	int	i;

	i = 3;
	while (i < FOPEN_MAX)
	{
		close(i);
		i++;
	}
}
