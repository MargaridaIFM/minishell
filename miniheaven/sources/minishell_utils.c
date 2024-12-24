/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:10:50 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/17 03:13:19 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**add_string_to_array(char **array, char *new_string)
{
	char	**new_array;
	int		i;

	i = 0;
	while (array && array[i] != NULL)
		i++;
	new_array = realloc(array, sizeof(char *) * (i + 2));
	if (!new_array)
	{
		ft_putendl_fd("Failed to allocate memory", 2);
		return (NULL);
	}
	new_array[i] = strdup(new_string);
	if (!new_array[i])
	{
		ft_putendl_fd("Failed to duplicate string", 2);
		return (NULL);
	}
	new_array[i + 1] = NULL;
	return (new_array);
}
