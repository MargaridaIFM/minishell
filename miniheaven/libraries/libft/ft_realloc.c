/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:29:42 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/18 22:43:43 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_realloc(void *ptr, size_t old_size, size_t new_size) {
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    void *new_ptr = malloc(new_size);
    if (!new_ptr) {
        return NULL; // Falha na alocação
    }

    if (ptr) {
        // Copiar os dados do buffer antigo para o novo
        size_t copy_size = old_size < new_size ? old_size : new_size;
        ft_memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }

    return new_ptr;
}
