/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:50:57 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/14 18:10:04 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"
// apagar ?
// t_token	*create_node(void)
// {
// 	t_token	*node;

// 	node = malloc(sizeof(t_token));
// 	return (node);
// }

// // apagar
// void	add_token_between(t_minishell *minishell, t_token *current, char *str)
// {
// 	t_token	*new_node;

// 	if (!current)
// 		return ;
// 	new_node = malloc(sizeof(t_token));
// 	if (!new_node)
// 		free_exit(minishell, "Error - Fail allocating token in split\n");
// 	new_node->type = WORD;
// 	new_node->str = ft_strdup(str);
// 	new_node->cmd = NULL;
// 	new_node->path = NULL;
// 	if (!new_node->str)
// 		free_exit(minishell, "Error - Fail allocating token str in split\n");
// 	if (current->next)
// 		new_node->next = current->next;
// 	else
// 		new_node->next = NULL;
// 	current->next = new_node;
// }
