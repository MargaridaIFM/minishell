/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:34:18 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/18 11:59:51 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_total_strings(t_minishell *minishell, t_ast *ast)
{
	t_ast	*temp;
	int		total;
	int		i;

	total = 0;
	temp = ast;
	while (temp->token->type <= 3)
	{
		if (temp->token->cmd)
		{
			i = 0;
			while (temp->token->cmd[i])
			{
				total++;
				i++;
			}
		}
		if (open_file(minishell, temp) == -1)
		{
			failed_to_open(minishell);
			return (-1);
		}
		temp = temp->right;
	}
	return (total);
}

int	count_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**collect_commands(t_minishell *minishell, t_ast *ast)
{
	char	**cmd ;
	int		count;

	cmd = NULL;
	count = 0;
	if (ast->token->dq == 1 && ft_count_words(ast->token->str) > 1)
	{
		minishell->_str_ = 1;
	}
	while (ast)
	{
		cmd = process_ast_commands(ast, &count, cmd);
		ast = ast->right;
	}
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	execute_redir(t_minishell *minishell, t_ast *ast, int flag)
{
	char	**cmd;

	cmd = collect_commands_redirs(minishell, ast);
	printf("Infile %d stdin %d\n", minishell->infile, minishell->temp_stdin);
	if (cmd == NULL)
	{;
		rebuild_fileno(minishell);
		close_redir(minishell);
		if (minishell->_pipe_ == 1)
			free_exit(minishell, "");
		free_all(minishell, "");
		return ;
	}
	if (flag == -1)
		ft_execute(minishell, cmd);
	else if (minishell->_pipe_ == 1)
		ft_execute_pipe(minishell, cmd);
	rebuild_fileno(minishell);
	close_redir(minishell);
	return ;
}
