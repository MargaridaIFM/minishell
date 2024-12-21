/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:41:40 by mistery576        #+#    #+#             */
/*   Updated: 2024/10/30 11:53:12 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//wextitstatus - pesquisar e falar com a melhor parceira do mundo 

void	execute_ast(t_minishell *minishell, t_ast *ast, int flag)
{
	char	**cmd;

	cmd = NULL;
	if (ast->token->type <= 3)
	{
		execute_redir(minishell, ast, flag);
		return ;
	}
	if (ast->token->type == WORD || ast->token->type == STR)
	{
		cmd = collect_commands(minishell, ast);
		if (flag == -1)
			ft_execute(minishell, cmd);
		else
			ft_execute_pipe(minishell, cmd);
	}
	if (ast->token->type == PIPE)
	{
		if (ast->right->token->type != PIPE)
			do_one_pipe(minishell, ast);
		else
			do_pipeline(minishell, ast);
	}
	rebuild_fileno(minishell);
	close_redir(minishell);
}

void	error_execute(t_minishell *minishell,
		char **split_cmd, char *cmd_path)
{
	g_signal = 127;
	ft_putstr_fd(split_cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (cmd_path != NULL)
		free(cmd_path);
	free_array(split_cmd);
	free_exit(minishell, "");
}

int	find_builtin(t_minishell *minishell, char **dp)
{
	if (ft_strcmp(dp[0], "cd") == 0)
		return (ft_cd(dp, minishell), 1);
	else if (ft_strcmp(dp[0], "echo") == 0)
		return (ft_echo(dp), 1);
	else if (ft_strcmp(dp[0], "env") == 0)
		return (ft_env(minishell, dp), 1);
	else if (ft_strcmp(dp[0], "export") == 0)
		return (ft_export(minishell, dp), 1);
	else if (ft_strcmp(dp[0], "unset") == 0)
		return (ft_unset(dp, minishell), 1);
	else if (ft_strcmp(dp[0], "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(dp[0], "exit") == 0)
	{
		free_array(dp);
		free_exit(minishell, "");
	}
	return (0);
}

/**
 * @brief Vai executar o comando recebido 
 * pelo (split_cmd). Ele encontra primeiro o path,
 * na variavel minishell->envp, (ex /bin/ls), significa que executa o comando ls.
 * @param t_minishell *minishell, char **split_cmd
 * @return (void);
 */
void	ft_execute(t_minishell *minishell, char **cmd)
{
	int		child;

	if (redirect_read(minishell) == -1)
		free_exit(minishell, "Something went wrong with dup2\n");
	if (check_execute(minishell, cmd) == 1)
		return ;
	if (find_builtin(minishell, cmd) == 1)
	{
		minishell->exit_status = WEXITSTATUS(minishell->exit_status);
		return (free_array(cmd));
	}
	child = fork();
	if (child == 0)
		execute_cmd(minishell, cmd);
	else
		waitpid(child, &minishell->exit_status, 0);
	minishell->exit_status = WEXITSTATUS(minishell->exit_status);
	rebuild_fileno(minishell);
	free_array(cmd);
}
