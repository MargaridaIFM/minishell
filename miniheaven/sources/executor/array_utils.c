/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:49:14 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/28 20:14:39 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Joins array to the array_first
 * @param char **array_first, char *array
 * @return (char **)
 */
char	**join_array(char **array_first, char *array)
{
	char	**new_array;
	int		i;
	int		j;

	new_array = malloc(sizeof(char *) * (count_array(array_first) + 2));
	i = 0;
	j = 0;
	if (!new_array)
	{
		free_array(array_first);
		free(array);
	}
	while (array_first[i])
	{
		new_array[j] = strdup(array_first[i]);
		i++;
		j++;
	}
	new_array[j] = strdup(array);
	j++;
	new_array[j] = NULL;
	free_array(array_first);
	return (new_array);
}

char	**concat_arrays(char **arr1, char **arr2)
{
	char	**result;
	int		len1;
	int		len2;
	int		i;
	int		j;

	i = -1;
	j = 0;
	len1 = count_array(arr1);
	len2 = count_array(arr2);
	result = malloc((len1 + len2 + 1) * sizeof(char *));
	while (++i < len1)
		result[i] = arr1[i];
	while (j < len2)
	{
		result[i] = arr2[j];
		i++;
		j++;
	}
	result[i] = NULL;
	free(arr1);
	free(arr2);
	return (result);
}

char	**replace_null_with_empty(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i] == NULL)
		{
			str[i] = ft_strdup("");
		}
		i++;
	}
	return (str);
}

/**
 * @brief Util for the function copy_array
 */
/**
 * @brief Util for the function copy_array
 */
/**
 * @brief Handles the case when ast->token->expander == 1
 */
static int	handle_expander(t_ast *ast, char **cmd_array, int *i)
{
	char	**split_cmd;
	int		j;

	split_cmd = ft_split(ast->token->str, ' ');
	j = 0;
	while (split_cmd[j])
	{
		cmd_array[*i] = ft_strdup(split_cmd[j]);
		(*i)++;
		j++;
	}
	free_array(split_cmd);
	return (1);
}

/**
 * @brief Util for the function copy_array
 */
int	copy_token_to_array(t_ast *ast, char **cmd_array, int *i)
{
	if (ast->token->expander == 1)
	{
		return (handle_expander(ast, cmd_array, i));
	}
	else
	{
		cmd_array[*i] = ft_strdup(ast->token->str);
		if (!cmd_array[*i])
		{
			while (*i > 0)
				free(cmd_array[--(*i)]);
			free(cmd_array);
			return (0);
		}
		(*i)++;
	}
	return (1);
}
