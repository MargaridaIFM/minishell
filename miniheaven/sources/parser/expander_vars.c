/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:12:49 by mistery576        #+#    #+#             */
/*   Updated: 2025/01/07 10:49:46 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	expand_vars_utils1(t_minishell *minishell, t_token *token, int *idx)
{
	if (token->str[*idx] == '\'')
	{
		printf("Index 5: %d\n", *idx);
		if (!minishell->expander->dq)
		{
			printf("Index 5_1: %d\n", *idx);
			
			// rm_one_single_quotes(token, minishell, idx);
			// printf("Index 5_2: %d\n", *idx);
			// while(token->str[*idx] != '\'')
			// 	idx++;
			// printf("Index 5_3: %d\n", *idx);
			// rm_one_single_quotes(token, minishell, idx);
			// printf("Index 5_4: %d\n", *idx);

		}
	}
	else if (token->str[*idx] == '"')
	{
		rm_double_quote(token, minishell, idx);
		minishell->expander->dq = !minishell->expander->dq;
	}
}

static void	support(t_minishell *minishell,
	t_token *token, int *idx, char **new_str)
{
	if (minishell->expander->dq || !minishell->expander->dq)
	{
		printf("Index 2_2_4: %d\n", *idx);
		*idx = *idx - ft_strlen(minishell->expander->var_name) - 1;
		*new_str = replace_var_in_str(token->str, minishell, idx);
		free(token->str);
		token->str = *new_str;
		if (minishell->expander->dq
			&& ft_count_words(minishell->expander->var_content) > 1)
			token->type = STR;
	}
}

static void	expand_vars_utils2(t_minishell *minishell,
	t_token *token, int *idx, char **new_str)
{
	(*idx)++;
	printf("Index 2_2_1: %d\n", *idx);
	if (token->str[*idx] == '?')
	{
		minishell->expander->var_name = ft_strdup("?");
		(*idx)++;
	}
	// else if (token->str[*idx] == '\'')
	// 	rm_single_quotes(token, minishell, idx);
	else if (!ft_isalpha(token->str[*idx]) && token->str[*idx] != '_' )
	{
		printf("Index 2_2_2: %d\n", *idx);
		minishell->expander->var_name
			= add_char(token->str[*idx], minishell->expander->var_name);
		(*idx)++;
	}
	else
	{
		printf("Index 2_2_3: %d\n", *idx);
		while (token->str[*idx]
			&& (ft_isalnum(token->str[*idx])
				|| token->str[*idx] == '_'))
		{
			printf("Index 2_2_3_1: %d\n", *idx);
			minishell->expander->var_name
				= add_char(token->str[*idx], minishell->expander->var_name);
			(*idx)++;
		}
	}
	minishell->expander->var_content = extrat_var_content(minishell);
	support(minishell, token, idx, new_str);
}

void	expand_vars(t_minishell *minishell, t_token *token)
{
	int		idx;
	char	*new_str;

	idx = 0;
	if (minishell->expander == NULL)
		minishell->expander = malloc(sizeof(t_expand));
	if (!minishell->expander)
		free_exit(minishell, "Error - Fail allocating expander");
	reset_expand(minishell->expander);
	printf("Index 1: %d\n", idx);
	while (token->str[idx])
	{
		printf("Index 2: %d\n", idx);
		printf("str: %c\n", token->str[idx]);
		if (token->str[idx] == '$' && token->str[idx + 1] == '\'')
		{ 
			printf("Index 4: %d\n", idx);
			printf("str dollar: %s\n", token->str);
			
			rm_dollar(token, minishell, &idx);
			printf("str dollar apos: %s\n", token->str);

			printf("Index 4.1: %d\n", idx);

			rm_one_single_quotes(token, minishell, &idx);
			printf("Index 4.2: %d\n", idx);
			while(token->str[idx] != '\'')
				idx++;
			printf("Index 4.3: %d\n", idx);
				
			rm_one_single_quotes(token, minishell, &idx);

		}
		if (token->str[idx] == '$' && token->str[idx + 1] == '\"')
		{
			rm_dollar(token, minishell, &idx);
			idx--;
		}
		else if (token->str[idx] == '\'' || token->str[idx] == '"')
		{
			printf("Index 2_1: %d\n", idx);
			expand_vars_utils1(minishell, token, &idx);
			printf("str apos: %s\n", token->str);

		}
		else if (token->str[idx] == '$' && !token->str[idx + 1]
			&& !minishell->expander->dq)
			return ;
		else if (token->str[idx] == '$')
		{
			printf("Index 2_2: %d\n", idx);
			expand_vars_utils2(minishell, token, &idx, &new_str);
			free_expand(minishell->expander);
		}
		idx++;
	}
}
void rm_dollar(t_token *token, t_minishell *minishell, int *idx)
{
	int		i;
	char	*new_str;
	int j;
	
	printf("aqui\n");
	(void)minishell;
	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(token->str)));
	if (!new_str) {
        free_exit(minishell, "Error - Fail allocating memory for new str\n");
    }
	while(i < *idx)
	{
		new_str[i] = token->str[i];
		i++;
	}
	j = i;
	i++;
	while (token->str[i])
	{
		new_str[j] = token->str[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	free(token->str);
	token->str = new_str;
}
