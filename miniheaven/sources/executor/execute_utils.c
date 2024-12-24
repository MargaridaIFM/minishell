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

int	rebuild_fileno(t_minishell *minishell)
{
	if (minishell->infile != -1)
	{
		if (dup2(minishell->temp_stdin, STDIN_FILENO) == -1)
			return (-1);
		close(minishell->temp_stdin);
	}
	if (minishell->outfile != -1)
	{
		if (dup2(minishell->temp_stdout, STDOUT_FILENO) == -1)
			return (-1);
		close(minishell->temp_stdout);
	}
	return (0);
}

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

void	ft_execute_pipe(t_minishell *minishell, char **cmd)
{
	char	*cmd_path;

	redirect_read(minishell);
	if (check_execute(minishell, cmd) == 1)
		free_exit(minishell, "");
	if (find_builtin(minishell, cmd) == 1)
	{
		free_array(cmd);
		free_exit(minishell, "");
	}
	// if (ft_strncmp("cat", cmd[0], 3) == 0)
	// 	close(minishell->fd[0]);
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, minishell->envp) == -1)
			error_execute(minishell, cmd, NULL);
	}
	cmd_path = find_path(minishell, cmd[0]);
	if (cmd_path == NULL)
		error_execute(minishell, cmd, cmd_path);
	if (execve(cmd_path, cmd, minishell->envp) == -1)
		error_execute(minishell, cmd, cmd_path);
}

int	check_dir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	execute_cmd(t_minishell *minishell, char **split_cmd)
{
	char	*cmd_path;
	int		count;

	count = count_array(split_cmd);
	split_cmd = ft_split_cmd(split_cmd, count);
	if (access(split_cmd[0], X_OK) == 0)
		execve(split_cmd[0], split_cmd, minishell->envp);
	if (check_dir(split_cmd[0]) == 1)
	{
		g_signal = 126;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(split_cmd[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		free_array(split_cmd);
		free_exit(minishell, " ");
	}
	cmd_path = find_path(minishell, split_cmd[0]);
	if (cmd_path == NULL)
		error_execute(minishell, split_cmd, cmd_path);
	execve(cmd_path, split_cmd, minishell->envp);
}
