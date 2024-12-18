/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:29:31 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/18 11:51:23 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



char **copy_array(t_ast *ast, int count) {
    char **cmd_array;
    int i;

    cmd_array = malloc((count + 1) * sizeof(char *));
    if (!cmd_array)
        return (NULL);
    i = 0;
    while (ast && (ast->token->type == WORD || ast->token->type == STR)) 
    {
        cmd_array[i] = ft_strdup(ast->token->str);
        if (!cmd_array[i]) 
        {
            while (i > 0)
                free(cmd_array[--i]);
            free(cmd_array);
            return (NULL);
        }
        ast = ast->right;
        i++;
    }
    cmd_array[i] = NULL;
    return cmd_array;
}

char    **built_cmd(t_ast *ast)
{
    char    **cmd_array;
    int     count;
    t_ast   *temp;

    // Contar os tokens na árvore
    count = 0;
    temp = ast;
    while (temp && (temp->token->type == WORD || temp->token->type == STR)) 
    {
        count++;
        temp = temp->right;
    }
    // Usar a função para copiar tokens para o array
    cmd_array = copy_array(ast, count);
    return cmd_array;
}

