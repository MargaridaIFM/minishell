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

void wait_pipes(t_minishell *minishell, pid_t *pids, int num_commands)
{
	int i;

	i = 0;
	while (i < num_commands)
	{
		waitpid(pids[i], &minishell->exit_status, 0);
		i++;
	}
}

int	count_pipes(t_ast *ast)
{
	t_ast *temp;
	int commands;

	temp = ast;
	commands = 1;
	while (temp->token->type == PIPE)
	{
		commands++;
		temp = temp->right;
	}
	return commands;
}

void do_pipeline(t_minishell *minishell, t_ast *ast)
{
	pid_t pid;
	pid_t *pids;
	int prev_fd = STDIN_FILENO;
	int i = 0;
	int commands;

	minishell->commands = 0;
	minishell->_pipe_ = 1;
	commands = count_pipes(ast);
	pids = malloc(sizeof(pid_t) * commands);
	while (ast->token->type == PIPE)
	{
		pipe(minishell->fd); // Cria um pipe para o comando atual
		pid = fork();
		if (pid == 0) // Processo filho
		{
			dup2(prev_fd, STDIN_FILENO); // Conecta stdin ao pipe anterior
			dup2(minishell->fd[1], STDOUT_FILENO); // Conecta stdout ao próximo pipe
			close(minishell->fd[0]); // Fecha leitura do pipe no filho
			close(minishell->fd[1]); // Fecha escrita do pipe no filho
			execute_ast(minishell, ast->left, 1);
			exit(EXIT_SUCCESS);
		}
		else if (pid > 0) // Processo pai
		{
			close(minishell->fd[1]); // Fecha escrita no pipe no pai
			if (prev_fd != STDIN_FILENO)
				close(prev_fd); // Fecha a leitura do pipe anterior
			prev_fd = minishell->fd[0]; // Atualiza o pipe anterior para o próximo comando
			pids[i++] = pid;
		}
		else
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		ast = ast->right;
		minishell->commands++;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
		execute_ast(minishell, ast, 1);
	}
	else if (pid > 0)
	{
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		pids[i++] = pid;
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	wait_pipes(minishell, pids, minishell->commands);
	free(pids);
	minishell->_pipe_ = 0;
}

