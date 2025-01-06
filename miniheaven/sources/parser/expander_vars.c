/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:12:49 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/07 22:07:36 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Handles single and double quotes during variable expansion.
 * 
 * Single quotes are removed if not inside a double-quote block.
 *  Double quotes are removed and toggle the `dq` flag in the `expander`.
 * 
 * @param minishell Pointer to the `t_minishell` structure/
 * @param token Pointer to the token being processed.
 * @param idx Pointer to the current index in the token string.
 * 
 * @return Void. 
 */
static void	expand_vars_utils1(t_minishell *minishell, t_token *token, int *idx)
{
	if (token->str[*idx] == '\'')
	{
		if (!minishell->expander->dq)
			rm_single_quotes(token, minishell, idx);
	}
	else if (token->str[*idx] == '"')
	{
		rm_double_quote(token, minishell, idx);
		minishell->expander->dq = !minishell->expander->dq;
	}
}

/**
 * @brief Replaces a variable in the token string with its value.
 * 
 * This function replaces a variable's name in the token string with its value. 
 * It adjusts the string length, frees old memory, and updates the token
 * type if necessary.
 * 
 * @param minishell Pointer to the `t_minishell`.
 * @param token Pointer to the token being processed.
 * @param idx Pointer to the current index in the token string.
 * @param new_str Pointer to hold the newly allocated string after replacement.
 * 
 * @return Void.
 */
static void	support(t_minishell *minishell,
	t_token *token, int *idx, char **new_str)
{
	if (minishell->expander->dq || !minishell->expander->dq)
	{
		*idx = *idx - ft_strlen(minishell->expander->var_name) - 1;
		*new_str = replace_var_in_str(token->str, minishell, idx);
		free(token->str);
		token->str = *new_str;
		if (minishell->expander->dq
			&& ft_count_words(minishell->expander->var_content) > 1)
			token->type = STR;
	}
}

/**
 * @brief Extracts the variable name and replaces it with its content.
 * 
 * This function identifies a variable in the token string starting with `$`,
 * extracts its name,  * and retrieves its value using `extrat_var_content`.
 * 
 * @param minishell Pointer to the `t_minishell`.
 * @param token Pointer to the token being processed.
 * @param idx Pointer to the current index in the token string.
 * @param new_str Pointer to hold the newly allocated string after replacement.
 * 
 * @return Void.
 * 
 */
static void	expand_vars_utils2(t_minishell *minishell,
	t_token *token, int *idx, char **new_str)
{
	(*idx)++;
	if (token->str[*idx] == '?')
	{
		minishell->expander->var_name = ft_strdup("?");
		(*idx)++;
	}
	else if (!ft_isalpha(token->str[*idx]) && token->str[*idx] != '_')
	{
		minishell->expander->var_name
			= add_char(token->str[*idx], minishell->expander->var_name);
		(*idx)++;
	}
	else
	{
		while (token->str[*idx]
			&& (ft_isalnum(token->str[*idx])
				|| token->str[*idx] == '_'))
		{
			minishell->expander->var_name
				= add_char(token->str[*idx], minishell->expander->var_name);
			(*idx)++;
		}
	}
	minishell->expander->var_content = extrat_var_content(minishell);
	support(minishell, token, idx, new_str);
}
/**
 * @brief Expands environment variables and processes quotes in a token string.
 * 
 * This function handles the expansion of environment variables within a token's 
 * string by identifying and replacing variables prefixed with `$`. 
 * Processes single and double quotes to handle their special meaning 
 * Auxiliary functions are used for specific tasks like managing quotes, 
 * extracting variable content, and replacing variables in the string.
 * If a variable is not found, it is replaced with an empty string.
 * 
 * @param minishell Pointer to the `t_minishell` structure.
 * @param token Pointer to the token whose string will be processed and expanded.
 * 
 * @return Void. Modifies the token str.
 */

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
	while (token->str[idx])
	{
		if (token->str[idx] == '\'' || token->str[idx] == '"')
			expand_vars_utils1(minishell, token, &idx);
		else if (token->str[idx] == '$' && !token->str[idx + 1]
			&& !minishell->expander->dq)
			return ;
		else if (token->str[idx] == '$')
		{
			expand_vars_utils2(minishell, token, &idx, &new_str);
			free_expand(minishell->expander);
		}
		idx++;
	}
}
