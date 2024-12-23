/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:50:55 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/23 00:34:10 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**allocate_result_array(int total_strings)
{
	char	**result;

	result = malloc((total_strings + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

int	process_command(t_minishell *minishell, t_ast *ast,
		char **result, int *index)
{
	int	i;

	i = 0;
	if (ast->token->dq == 1 && minishell->_str_ == 0)
		minishell->_str_ = 1;
	else
		minishell->_str_ = 2;
	while (ast->token->cmd[i])
	{
		result[*index] = ft_strdup(ast->token->cmd[i]);
		if (!result[*index])
		{
			while (*index > 0)
			{
				(*index)--;
				free(result[*index]);
			}
		}
		(*index)++;
		i++;
	}
	return (0);
}

char	**process_ast_commands_redir(t_minishell *minishell,
			t_ast *ast, int total_strings)
{
	t_ast	*temp;
	char	**result;
	int		index;
	
	temp = ast;
	result = allocate_result_array(total_strings);
	if (!result)
		return (NULL);
	index = 0;
	while (temp)
	{
		if (temp->token->cmd
			&& process_command(minishell, temp, result, &index) == -1)
		{
			free(result);
			return (NULL);
		}
		open_file(minishell, temp);
		temp = temp->right;
	}
	result[index] = NULL;
	return (result);
}

//Função principal para concatenar arrays de strings de ast->cmd
char	**collect_commands_redirs(t_minishell *minishell, t_ast *ast)
{
	char	**result;
	int		total_strings;

	total_strings = count_total_strings(ast);
	if (total_strings != 0)
	{
		result = process_ast_commands_redir(minishell, ast, total_strings);
		if (!result)
			return (NULL);
		return (result);
	}
	else
	{
		while (ast->token->type <= 3)
		{
			open_file(minishell, ast);
			ast = ast->right;
		}
		return (NULL);
	}
}

char	**process_ast_commands(t_ast *ast, int *count, char **cmd)
{
	char	**new_cmd;
	int		i;

	i = 0;
	new_cmd = malloc(sizeof(char *) * (*count + 2));
	if (!new_cmd)
		return (NULL);
	while (i < *count)
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	if (ft_strlen(ast->token->str) == 0)
		new_cmd[i] = ft_strdup("\"\"");
	else
		new_cmd[i] = ft_strdup(ast->token->str);
	if (!new_cmd[i])
	{
		free(new_cmd);
		return (NULL);
	}
	(*count)++;
	new_cmd[*count] = NULL;
	if (cmd)
		free(cmd);
	return (new_cmd);
}
