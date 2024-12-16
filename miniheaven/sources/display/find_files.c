/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:56:30 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/06 17:56:30 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_token	*copy_token_list(const t_token *token)
// {
// 	t_token	*copy;

// 	if (!token)
// 		return (NULL);
// 	copy = malloc(sizeof(t_token));
// 	if (!copy)
// 		return (NULL);
// 	copy->type = token->type;
// 	copy->str = ft_strdup(token->str);
// 	copy->path = ft_strdup(token->path);
// 	copy->cmd = ft_strdup(token->cmd);
// 	copy->next = copy_token_list(token->next);
// 	return (copy);
// }

t_ast	*copy_ast(t_ast *original)
{
	t_ast	*copy;

	if (!original)
		return (NULL);
	copy = malloc(sizeof(t_ast));
	if (!copy)
		return (NULL);
	if (original->token)
	{
		copy->token = malloc(sizeof(t_token));
		if (!copy->token)
		{
			free(copy);
			return (NULL);
		}
		copy->token->type = original->token->type;
		copy->token->str = ft_strdup(original->token->str);
		copy->token->path = ft_strdup(original->token->path);
		copy->token->cmd = ft_strdup(original->token->cmd);
		copy->token->next = NULL;
	}
	copy->left = copy_ast(original->left);
	copy->right = copy_ast(original->right);
	return (copy);
}

void	no_pipe(t_ast *temp_copy, t_ast *orig, t_ast *save_node)
{
	char	*cmd_built;

	cmd_built = NULL;
	if (temp_copy->left)
		orig->token->cmd = built_cmd(save_node->left);
	if (temp_copy->right->token->type > 3 && temp_copy->right->right)
	{
		cmd_built = built_cmd(temp_copy->right->right);
		orig->token->cmd = ft_strjoin_gnl(orig->token->cmd, " ");
		orig->token->cmd = ft_strjoin_gnl(orig->token->cmd, cmd_built);
		free(cmd_built);
	}
}

void	find_commands(t_ast *orig, t_ast *temp_copy, int flag)
{
	t_ast	*save_node;
	char	*cmd_built;

	cmd_built = NULL;
	save_node = temp_copy;
	if (flag == 0)
		no_pipe(temp_copy, orig, save_node);
	else if (temp_copy->right->token->type > 3
		&& temp_copy->right->right)
	{
		if (temp_copy->left && temp_copy->left->right)
			orig->token->cmd = built_cmd(save_node->left->right);
		if (orig->token->cmd)
		{
			cmd_built = built_cmd(temp_copy->right->right);
			orig->token->cmd = ft_strjoin_gnl(orig->token->cmd, " ");
			orig->token->cmd = ft_strjoin_gnl(orig->token->cmd, cmd_built);
			free(cmd_built);
		}
		else
			orig->token->cmd = built_cmd(temp_copy->right->right);
	}
	else if (temp_copy->left && temp_copy->left->right)
		orig->token->cmd = built_cmd(temp_copy->left->right);
}

void	find_files(t_ast *orig, t_ast *temp_copy, t_minishell *minishell)
{
	while (temp_copy && orig)
	{
		if (temp_copy->token->type == PIPE)
			minishell->first = 0;
		if (temp_copy->left)
			find_files(orig->left, temp_copy->left, minishell);
		if (temp_copy->token->type == PIPE)
			minishell->first = 0;
		if (temp_copy->token->type <= 3)
		{
			find_commands(orig, temp_copy, minishell->first);
			if (temp_copy->right->token->type <= 3)
				orig->token->path
					= ft_strdup(temp_copy->right->left->token->str);
			else
				orig->token->path = ft_strdup(temp_copy->right->token->str);
			minishell->first = 1;
		}
		temp_copy = temp_copy->right;
		orig = orig->right;
	}
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
