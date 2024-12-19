/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:16:39 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/19 17:50:01 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **join_arrays(char **array_first, char *array)
{
    char **new_array;
	int i;
	int j;
		
    new_array = malloc(sizeof(char *) * (count_array(array_first) + 2));
    i = 0;
	j = 0;
	if(!new_array)
	{
		free_array(array_first);
		free(array);
        //free_all(minishell,"Fail alocating **array\n");
	}
	while(array_first[i])
	{
		new_array[j] = strdup(array_first[i]); // proteger contra falha ? 
		i++;
		j++;
	}
	new_array[j] = strdup(array);
	j++;
	new_array[j] = NULL;
	free_array(array_first);
	//free(array);
	return(new_array); 
}

