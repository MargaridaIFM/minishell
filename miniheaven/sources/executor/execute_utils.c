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

void	ft_execute_pipe(t_minishell *minishell, char **cmd)
{
	char	*cmd_path;

	redirect_read(minishell);
	if (my_getenv(minishell, "PATH") == NULL)
	{
		printf("%s: command not found\n", cmd[0]);
		error_execute(minishell, cmd, NULL);
	}
	if (find_builtin(minishell, cmd) == 1)
	{
		free_array(cmd);
		free_exit(minishell, "");
	}
	if (ft_strncmp("cat", cmd[0], 3) == 0)
		close(minishell->fd[0]);
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

char **ft_split_cmd(char **cmd, int cmd_count) {
    char **result;
    int result_count;
    int result_size;
	char **tokens;

	result = NULL;
	result_count = 0;
	result_size = 0;
    for (int i = 0; i < cmd_count; i++) {
        tokens = ft_split(cmd[i], ' ');
        if (!tokens) 
			continue;
        for (int j = 0; tokens[j] != NULL; j++) {
            if (result_count >= result_size) {
                int new_size = result_size == 0 ? 4 : result_size * 2;
                result = ft_realloc(result, result_size * sizeof(char *), new_size * sizeof(char *));
                if (!result)
				{
                    perror("Error reallocating memory");
                    exit(EXIT_FAILURE);
                }
                result_size = new_size;
            }
            result[result_count] = tokens[j];
            result_count++;
		}
        free(tokens);
    }
    if (result_count >= result_size) {
        result = ft_realloc(result, result_size * sizeof(char *), (result_count + 1) * sizeof(char *));
        if (!result) {
            perror("Error reallocating memory");
            exit(EXIT_FAILURE);
        }
    }
    result[result_count] = NULL;
	free_array(cmd);
    return result;
}

int		check_dir(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return 1;
		i++;
	}
	return 0;
}

void	execute_cmd(t_minishell *minishell, char **split_cmd, char *cmd)
{
	(void)cmd;
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
