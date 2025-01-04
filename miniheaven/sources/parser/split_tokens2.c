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
t_token	*create_node(void)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	return (node);
}

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ft_count_words(char const *s)
{
	int	counter;
	int	idx;

	counter = 0;
	idx = 0;
	while (s[idx] && is_delimiter(s[idx]))
		idx++;
	while (s[idx])
	{
		if (!is_delimiter(s[idx]))
			counter++;
		while (s[idx] && !is_delimiter(s[idx]))
			idx++;
		while (s[idx] && is_delimiter(s[idx]))
			idx++;
	}
	return (counter);
}
// apagar
void	add_token_between(t_minishell *minishell, t_token *current, char *str)
{
	t_token	*new_node;

	if (!current)
		return ;
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		free_exit(minishell, "Error - Fail allocating token in split\n");
	new_node->type = WORD;
	new_node->str = ft_strdup(str);
	new_node->cmd = NULL;
	new_node->path = NULL;
	if (!new_node->str)
		free_exit(minishell, "Error - Fail allocating token str in split\n");
	if (current->next)
		new_node->next = current->next;
	else
		new_node->next = NULL;
	current->next = new_node;
}
