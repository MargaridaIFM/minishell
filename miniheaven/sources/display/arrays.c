/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:16:39 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/19 14:17:30 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **join_arrays(t_minishell *minishell, char **array_first, char **array_sec)
{
    char **new_array;

    new_array = malloc(sizeof(char *) * (count_array(array_first) + count_array(array_sec)));
    if(!new_array)
        free_exit(minishell,"Fail alocating **array\n");
        
    
}