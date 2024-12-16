/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:26:45 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/06 19:26:45 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_pipeline(t_minishell *minishell, t_ast *ast)
{
	int	final;

	minishell->commands = 1;
	minishell->_pipe_ = 1;
	minishell->temp_stdin = dup(STDIN_FILENO);
	while (ast->token->type == PIPE)
	{
		minishell->commands++;
		pipe_fork(minishell, ast);
		ast = ast->right;
	}
	final = fork();
	if (final == 0)
		execute_ast(minishell, ast, 1);
	wait_pipes(minishell);
	minishell->_pipe_ = 0;
	dup2(minishell->temp_stdin, STDIN_FILENO);
	close(minishell->temp_stdin);
}

void	pipe_fork(t_minishell *minishell, t_ast *ast)
{
	pid_t	child;

	fork_and_pipe(minishell, ast->left, &child);
	if (child == 0)
	{
		execute_ast(minishell, ast->left, 1);
		return ;
	}
}

void	fork_and_pipe(t_minishell *minishell, t_ast *ast, int *child)
{
	(void)ast;
	pipe(minishell->fd);
	*child = fork();
	redir_pipe(minishell, *child);
}

void	redir_pipe(t_minishell *minishell, int child)
{
	if (child == 0)
		dup2(minishell->fd[1], STDOUT_FILENO);
	else
	{
		dup2(minishell->fd[0], STDIN_FILENO);
		close(minishell->fd[0]);
		close(minishell->fd[1]);
	}
}

void	wait_pipes(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->commands)
	{
		waitpid(-1, &minishell->exit_status, 0);
		i++;
	}
}
