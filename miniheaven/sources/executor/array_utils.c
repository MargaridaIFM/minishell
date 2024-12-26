/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:49:14 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/26 20:58:19 by mistery576       ###   ########.fr       */
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
