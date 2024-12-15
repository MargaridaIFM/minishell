/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:22:16 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/14 01:29:10 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_one_pipe(t_minishell *minishell, t_ast *ast)
{
	pid_t	right_fork;
	pid_t	left_fork;
	
	minishell->temp_stdin = dup(STDIN_FILENO);
	pipe(minishell->fd);
	left_fork = fork();
	if (left_fork == 0)
	{
		dup2(minishell->fd[1], STDOUT_FILENO);
		close(minishell->fd[1]);
		close(minishell->fd[0]);
		execute_ast(minishell, ast->left, -1);
		free_exit(minishell, "");
	}
	right_fork = fork();
	if (right_fork == 0) 
	{
        dup2(minishell->fd[0], STDIN_FILENO);
       	close(minishell->fd[1]);
		close(minishell->fd[0]);
        execute_ast(minishell, ast->right, -1);
        free_exit(minishell, ""); // Se falhar, encerra o processo
	}
	close (minishell->fd[1]);
	close(minishell->fd[0]);
	waitpid(left_fork, &minishell->exit_status , 0);
	//minishell->exit_status = WEXITSTATUS(minishell->exit_status);
	waitpid(right_fork, &minishell->exit_status, 0);
	//minishell->exit_status = WEXITSTATUS(minishell->exit_status);
	//dup2(minishell->temp_stdin, STDIN_FILENO);
	//close(minishell->temp_stdin);
	//minishell->temp_stdin = -1;
	//free_exit(minishell, "");
}