/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:29:31 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/18 11:51:23 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_array(t_ast *ast, int count)
{
	char	**cmd_array;
	int		i;

	cmd_array = malloc((count + 1) * sizeof(char *));
	if (!cmd_array)
		return (NULL);
	i = 0;
	while (ast && (ast->token->type == WORD || ast->token->type == STR))
	{
		cmd_array[i] = ft_strdup(ast->token->str);
		if (!cmd_array[i])
		{
			while (i > 0)
				free(cmd_array[--i]);
			free(cmd_array);
			return (NULL);
		}
		ast = ast->right;
		i++;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

char	**built_cmd(t_ast *ast)
{
	t_ast	*temp;
	char	**cmd_array;
	int		count;

	count = 0;
	temp = ast;
	while (temp && (temp->token->type == WORD || temp->token->type == STR))
	{
		count++;
		temp = temp->right;
	}
	cmd_array = copy_array(ast, count);
	return (cmd_array);
}

void	set_redirs(t_minishell *minishell, t_ast *ast)
{
	t_ast	*copy;
	t_ast	*orig;
	t_ast	*temp_copy;

	copy = copy_ast(ast);
	if (!copy)
		free_exit(minishell, "Failed to create a copy\n");
	orig = ast;
	temp_copy = copy;
	find_files(orig, temp_copy, minishell);
	free_ast(copy);
}

void	no_pipe_util(t_ast *orig, t_ast *temp_copy)
{
	if (orig->token->cmd)
	{
		temp_copy = temp_copy->right->right;
		while (temp_copy)
		{
			orig->token->cmd
				= join_array(orig->token->cmd, temp_copy->token->str);
			temp_copy = temp_copy->right;
		}
	}
	else
	{
		if (orig->right->right->token->dq == 1
			&& ft_count_words(temp_copy->right->right->token->str) > 1)
		{
			orig->token->dq = 1;
		}
		orig->token->cmd = built_cmd(temp_copy->right->right);
	}
}

void	complete_last_redir(t_ast *temp_copy, t_ast *orig, t_ast *save_node)
{
	if (temp_copy->left && temp_copy->left->right)
	{
		if (orig->left->right->token->dq == 1)
			orig->left->right->token->dq = 1;
		orig->token->cmd = built_cmd(save_node->left->right);
	}
	if (orig->token->cmd && temp_copy->right->right)
	{
		temp_copy = temp_copy->right->right;
		if (temp_copy->token->dq == 1)
			orig->token->dq = 1;
		while (temp_copy)
		{
			orig->token->cmd
				= join_array(orig->token->cmd, temp_copy->token->str);
			temp_copy = temp_copy->right;
		}
	}
	else
	{
		if (temp_copy->right->right->token->dq == 1)
			orig->token->dq = 1;
		orig->token->cmd = built_cmd(temp_copy->right->right);
	}
}
