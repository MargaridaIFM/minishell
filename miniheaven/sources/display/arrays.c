/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:16:39 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/19 17:24:09 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **join_arrays(t_minishell *minishell, char **array_first, char **array_sec)
{
    char **new_array;
	int i;
	int j;
	
    new_array = malloc(sizeof(char *) * (count_array(array_first) + count_array(array_sec) + 1));
    i = 0;
	j = 0;
	if(!new_array)
	{
		free_array(array_first);
		free_array(array_sec);
        free_all(minishell,"Fail alocating **array\n");
	}
	while(array_first[i])
	{
		new_array[j] = strdup(array_first[i]); // proteger contra falha ? 
		i++;
		j++;
	}
	i = 0;
	while(array_sec[i])
	{
		new_array[j] = strdup(array_sec[i]);
		i++;
		j++;
	}   
	new_array[i] = NULL;
	return(new_array); 
}
