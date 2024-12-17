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

char **add_string_to_array(char **array, char *new_string)
{
    int i = 0;

    while (array && array[i] != NULL)
        i++;
    char **new_array = realloc(array, sizeof(char *) * (i + 2));
    if (!new_array)
    {
        perror("Erro ao realocar memória");
        return NULL;
    }
    new_array[i] = strdup(new_string);
    if (!new_array[i])
    {
        perror("Erro ao duplicar string");
        return NULL;
    }
    new_array[i + 1] = NULL;
    return new_array;
}