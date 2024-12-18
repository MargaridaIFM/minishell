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
	//free(cmd);
	if (execve(cmd_path, cmd, minishell->envp) == -1)
		error_execute(minishell, cmd, cmd_path);
	free_array(cmd);
	exit(0);
	// }
	// else
	// 	free_exit(minishell, "");
}

char **ft_split_cmd(char **cmd, int cmd_count) {
    char **result = NULL;   // Array para armazenar os tokens
    int result_count = 0;   // Contador para o número total de tokens
    int result_size = 0;    // Capacidade alocada (em elementos)

    // Iterar sobre cada comando na lista original
    for (int i = 0; i < cmd_count; i++) {
        // Obter os tokens da string atual usando ft_split
        char **tokens = ft_split(cmd[i], ' ');
        if (!tokens) continue; // Garantir que ft_split não retornou NULL

        // Adicionar os tokens ao array de resultados
        for (int j = 0; tokens[j] != NULL; j++) {
            // Realocar espaço para o novo token, se necessário
            if (result_count >= result_size) {
                int new_size = result_size == 0 ? 4 : result_size * 2; // Crescimento exponencial
                result = ft_realloc(result, result_size * sizeof(char *), new_size * sizeof(char *));
                if (!result) {
                    perror("Error reallocating memory");
                    exit(EXIT_FAILURE);
                }
                result_size = new_size;
            }

            // Adicionar o token ao array
            result[result_count] = tokens[j];
            result_count++;
        }

        free(tokens); // Liberar o array intermediário do ft_split (não as strings)
    }

    // Adicionar NULL no final do array de resultados
    if (result_count >= result_size) {
        result = ft_realloc(result, result_size * sizeof(char *), (result_count + 1) * sizeof(char *));
        if (!result) {
            perror("Error reallocating memory");
            exit(EXIT_FAILURE);
        }
    }
    result[result_count] = NULL;

    return result;
}

// char **ft_split_cmd(char **cmd, int cmd_count) {
//     char **result = NULL;
//     int result_count = 0;

//     // Iterar sobre cada comando na lista original
//     for (int i = 0; i < cmd_count; i++) {
//         char *temp = ft_strdup(cmd[i]);
//         char *token = strtok(temp, " ");

//         while (token != NULL) 
// 		{
//             result = ft_realloc(result, result_size * sizeof(char *), (result_count + 1) * sizeof(char *));
//             result[result_count] = strdup(token);
//             result_count++;
//             token = strtok(NULL, " ");
//         }
//         free(temp);
//     }
//     result = ft_realloc(result, result_size * sizeof(char *), (result_count + 1) * sizeof(char *));
//     result[result_count] = NULL;

//     return result;
// }

void	execute_cmd(t_minishell *minishell, char **split_cmd, char *cmd)
{
	(void)cmd;
	char	*cmd_path;
	int		count;

	count = count_array(split_cmd);
	split_cmd = ft_split_cmd(split_cmd, count);
	if (access(split_cmd[0], X_OK) == 0)
		execve(split_cmd[0], split_cmd, minishell->envp);
	cmd_path = find_path(minishell, split_cmd[0]);
	if (cmd_path == NULL)
		error_execute(minishell, split_cmd, cmd_path);
	execve(cmd_path, split_cmd, minishell->envp);
}
