/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:53:44 by mfrancis          #+#    #+#             */
/*   Updated: 2024/10/29 20:25:08 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_ast	*create_ast(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	if (check_symbol(tokens, PIPE) == 1)
		return (split_tokens_ast(&tokens, PIPE));
	else if (check_redir(tokens) != NO_TYPE)
		return (split_tokens_ast(&tokens, check_redir(tokens)));
	else
		return (add_right(&tokens));
	return (NULL);
}

t_tk_tp	check_redir(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type < WORD)
			return (temp->type);
		temp = temp->next;
	}
	return (NO_TYPE);
}

int	check_symbol(t_token *tokens, t_tk_tp symbol)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == symbol)
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_ast	*add_right(t_token **tokens)
{
	t_token	*temp;
	t_token	*next;
	t_ast	*ast;

	temp = *tokens;
	ast = new_ast_node(temp);
	if (temp != NULL)
		next = temp->next;
	else
		next = NULL;
	ast->right = create_ast(next);
	return (ast);
}

t_ast	*new_ast_node(t_token *tokens)
{
	t_ast	*new_node;

	if (!tokens)
		return (NULL);
	new_node = malloc(sizeof (t_ast));
	if (!new_node)
		return (NULL);
	new_node->token = tokens;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}
