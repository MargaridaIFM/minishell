/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:31:58 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/08 01:41:09 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_utils(t_token	**last, t_token	**temp, t_tk_tp symbol)
{
	(void)last;
	while (*temp)
	{
		if ((*temp)->type == symbol)
			break ;
		*last = *temp;
		*temp = (*temp)->next;
	}
}

t_ast	*split_tokens_ast(t_token **tokens, t_tk_tp symbol)
{
	t_token	*temp;
	t_token	*last;
	t_token	*next;
	t_ast	*ast;

	temp = *tokens;
	last = NULL;
	split_utils(&last, &temp, symbol);
	ast = new_ast_node(temp);
	if (last)
		last->next = NULL;
	if (temp != NULL)
		next = temp->next;
	else
		next = NULL;
	if (temp->next)
		temp->next = NULL;
	if (temp == *tokens)
		ast->left = create_ast(NULL);
	else
		ast->left = create_ast(*tokens);
	ast->right = create_ast(next);
	return (ast);
}
