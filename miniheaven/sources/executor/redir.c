/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:38:11 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/16 16:38:11 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file_util(t_minishell *minishell, t_ast *ast, char *file)
{
	if (ast->token->type == REDIR_IN)
	{
		if (access(file, F_OK) != 0)
		{
			printf("bash: %s: No such file or directory\n", file);
			return (-1);
		}
		if (minishell->infile != -1)
			close(minishell->infile);
		minishell->infile = open(file, O_RDONLY, 0644);
	}
	if (ast->token->type == REDIR_OUT || ast->token->type == REDIR_APPEND)
	{
		if (minishell->outfile != -1)
			close(minishell->outfile);
		if (ast->token->type == REDIR_OUT)
			minishell->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else
			minishell->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
	}
	return (0);
}

int	open_file(t_minishell *minishell, t_ast *ast)
{
	char		*file;
	t_heredoc	*temp_here;

	temp_here = minishell->heredoc;
	file = ast->token->path;
	if (open_file_util(minishell, ast, file) == -1)
		return (-1);
	else if (ast->token->type == REDIR_HEREDOC)
	{
		if (minishell->infile != -1)
			close(minishell->infile);
		minishell->infile = dup(minishell->heredoc->fd[0]);
		close(minishell->heredoc->fd[0]);
		free(minishell->heredoc->delimiter);
		temp_here = minishell->heredoc->next;
		minishell->heredoc = temp_here;
	}
	return (0);
}

int	redirect_read(t_minishell *minishell)
{
	if (minishell->infile != -1)
	{
		if (minishell->_pipe_ == 0)
			minishell->temp_stdin = dup(STDIN_FILENO);
		if (dup2(minishell->infile, STDIN_FILENO) == -1)
			return (-1);
		close(minishell->infile);
	}
	if (minishell->outfile != -1)
	{
		minishell->temp_stdout = dup(STDOUT_FILENO);
		if (dup2(minishell->outfile, STDOUT_FILENO) == -1)
			return (-1);
		close(minishell->outfile);
	}
	return (0);
}

void	redir_in(t_minishell *minishell, t_ast *ast, int flag)
{
	t_ast	*node_cmd;

	node_cmd = ast;
	if (open_file(minishell, ast) == 0)
	{
		if (ast->right->token->type == REDIR_OUT)
		{
			while (ast->right->token->type == REDIR_OUT)
			{
				if (minishell->outfile != -1)
					close(minishell->outfile);
				ast = ast->right;
				open_file(minishell, ast);
			}
			execute_ast(minishell, node_cmd->right->left->right, flag);
		}
		else
			execute_ast(minishell, ast->right->right, flag);
	}
}

void	redir_out(t_minishell *minishell, t_ast *ast, int flag)
{
	t_ast	*node_cmd;

	node_cmd = ast->left;
	while (ast->token->type == REDIR_OUT)
	{
		if (minishell->outfile != -1)
			close(minishell->outfile);
		open_file(minishell, ast);
		ast = ast->right;
	}
	execute_ast(minishell, node_cmd, flag);
}
