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

char	*built_cmd(t_ast *ast)
{
	char	*cmd;

	cmd = NULL;
	free(cmd);
	if (!cmd)
	{
		cmd = ft_strdup(ast->token->str);
	}
	while (ast->right && (ast->token->type == WORD || ast->token->type == STR))
	{
		cmd = ft_strjoin_gnl(cmd, " ");
		cmd = ft_strjoin_gnl(cmd, ast->right->token->str);
		ast = ast->right;
	}
	return (cmd);
}

void	execute_ast(t_minishell *minishell, t_ast *ast, int flag)
{
	char	**cmd;
	//int		i;

	//i = 0;
	cmd = NULL;
	if (ast->token->type <= 3)
		cmd = collect_commands_redirs(ast, minishell);
	if (cmd != NULL)
	{
		if (flag == -1)
			ft_execute(minishell, cmd);
		else
			ft_execute_pipe(minishell, cmd[0]);
		rebuild_fileno(minishell);
		close_redir(minishell);
		free(*cmd);
		return ;
	}
	if (ast->token->type == WORD || ast->token->type == STR)
	{
		cmd = collect_commands(ast);
		if (flag == -1)
			ft_execute(minishell, cmd);
		else
			ft_execute_pipe(minishell, cmd[0]);
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
		char **split_cmd, char *cmd_path, char *cmd)
{
	g_signal = 127;
	printf("%s: command not found\n", cmd);
	if (cmd_path != NULL)
		free(cmd_path);
	free(cmd);
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
		return (ft_env(minishell), 1);
	else if (ft_strcmp(dp[0], "export") == 0)
		return (ft_export(minishell), 1);
	else if (ft_strcmp(dp[0], "unset") == 0)
		return (ft_unset(dp, minishell), 1);
	else if (ft_strcmp(dp[0], "pwd") == 0)
		return (ft_pwd(minishell), 1);
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
	if (find_builtin(minishell, cmd) == 1)
	{
		minishell->exit_status = WEXITSTATUS(minishell->exit_status);
		return (free_array(cmd));
	}
	if (my_getenv(minishell, "PATH") == NULL)
	{
		printf("%s: command not found\n", cmd[0]);
		g_signal = 127;
		return (free_array(cmd));
	}
	child = fork();
	if (child == 0)
		execute_cmd(minishell, cmd, cmd[0]);
	else
		waitpid(child, &minishell->exit_status, 0);
	minishell->exit_status = WEXITSTATUS(minishell->exit_status);
	rebuild_fileno(minishell);
	free_array(cmd);
}
