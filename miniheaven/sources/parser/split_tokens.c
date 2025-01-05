/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 00:16:04 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/08 00:29:43 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// remover
// static void	split_tokens_utils(t_minishell *minishell,
// 	t_token **current, char *new_str, int idx)
// {
// 	char	*test;
// 	char	*trimmed;

// 	trimmed = NULL;
// 	test = NULL;
// 	test = ft_substr((*current)->str, idx,
// 			ft_strlen((*current)->str) - idx);
// 	if (!test)
// 	{
// 		free(new_str);
// 		free_exit(minishell,
// 			"Error - Allocation failed for 'test' in split_tokens\n");
// 	}
// 	trimmed = ft_strtrim(test, " \t\n");
// 	free(test);
// 	add_token_between(minishell, (*current), trimmed);
// 	free(trimmed);
// 	free((*current)->str);
// 	(*current)->str = new_str;
// 	(*current) = (*current)->next;
// 	new_str = NULL;
// }

// void	split_tokens(t_minishell *minishell, t_token **current)
// {
// 	int		idx;
// 	int		nbr_words;
// 	char	*new_str;

// 	idx = 0;
// 	new_str = NULL;
// 	if ((*current)->type == STR)
// 		return ;
// 	nbr_words = ft_count_words((*current)->str);
// 	while (nbr_words > 1)
// 	{
// 		while (is_delimiter((*current)->str[idx]))
// 			idx++;
// 		while ((*current)->str[idx] && !is_delimiter((*current)->str[idx]))
// 		{
// 			new_str = add_char((*current)->str[idx], new_str);
// 			idx++;
// 		}
// 		if (new_str)
// 			split_tokens_utils(minishell, current, new_str, idx);
// 		idx = 0;
// 		nbr_words--;
// 	}
// }
