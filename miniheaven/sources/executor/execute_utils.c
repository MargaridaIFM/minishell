/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:45:40 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/16 14:45:40 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_redir(t_minishell *minishell)
{
	if (minishell->infile != -1)
	{
		close(minishell->infile);
		minishell->infile = -1;
	}
	if (minishell->outfile != -1)
	{
		close(minishell->outfile);
		minishell->outfile = -1;
	}
}

void	ft_execute_pipe(t_minishell *minishell, char *cmd)
{
	char	**split_cmd;
	char	*cmd_path;

	split_cmd = ft_split(cmd, ' ');
	redirect_read(minishell);
	if (my_getenv(minishell, "PATH") == NULL)
	{
		printf("%s: command not found\n", split_cmd[0]);
		error_execute(minishell, split_cmd, NULL, cmd);
	}
	if (find_builtin(minishell, split_cmd, cmd) == 1)
	{
		free(cmd);
		free_array(split_cmd);
		free_exit(minishell, "");
	}
	if (ft_strcmp("cat", cmd) == 0)
		close(minishell->fd[0]);
	if (access(split_cmd[0], X_OK) == 0)
	{
		if (execve(split_cmd[0], split_cmd, minishell->envp) == -1)
			error_execute(minishell, split_cmd, NULL, cmd);
	}
	cmd_path = find_path(minishell, split_cmd[0]);
	if (cmd_path == NULL)
		error_execute(minishell, split_cmd, cmd_path, cmd);
	// free(cmd);
	if (execve(cmd_path, split_cmd, minishell->envp) == -1)
		error_execute(minishell, split_cmd, cmd_path, cmd);
	free_array(split_cmd);
	exit(0);
	// }
	// else
	// 	free_exit(minishell, "");
}

void	execute_cmd(t_minishell *minishell, char **split_cmd, char *cmd)
{
	char	*cmd_path;

	if (minishell->_pipe_ == 1)
	{
		if (find_builtin(minishell, split_cmd, cmd) == 1)
		{
			rebuild_fileno(minishell);
			free(cmd);
			fd_clean();
			free_array(split_cmd);
			free_exit(minishell, "");
		}
	}
	if (access(split_cmd[0], X_OK) == 0)
		execve(split_cmd[0], split_cmd, minishell->envp);
	cmd_path = find_path(minishell, split_cmd[0]);
	if (cmd_path == NULL)
		error_execute(minishell, split_cmd, cmd_path, cmd);
	execve(cmd_path, split_cmd, minishell->envp);
}
