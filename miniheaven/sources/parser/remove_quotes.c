/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:00:18 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/12 17:08:08 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	rm_single_quotes(t_token *token, t_minishell *minishell, int *idx)
{
	int		start;
	int		end;
	int		new_idx;
	char	*new_str;

	start = *idx + 1;
	end = start;
	new_idx = 0;
	while (token->str[end] != '\'')
		end++;
	new_str = malloc(sizeof(char) * (ft_strlen(token->str) - 1));
	if (!new_str)
		free_exit(minishell, "Error - Fail allocating memory for new str\n");
	ft_memcpy(new_str, token->str, start - 1);
	new_idx = start - 1;
	ft_memcpy(new_str + new_idx, token->str + start, end - start);
	new_idx = new_idx + (end - start);
	ft_memcpy(new_str + new_idx, token->str + end + 1,
		(ft_strlen(token->str + end + 1) + 1));
	*(idx) = new_idx - 1;
	free(token->str);
	token->str = new_str;
}

void	rm_double_quote(t_token *token, t_minishell *minishell, int *idx)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(token->str)));
	if (!new_str)
		free_exit(minishell, "Error - Fail allocating memory for new str\n");
	while (token->str[i])
	{
		if (i != *idx)
		{
			new_str[j] = token->str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(token->str);
	token->str = new_str;
	*(idx) = *(idx) - 1;
}
