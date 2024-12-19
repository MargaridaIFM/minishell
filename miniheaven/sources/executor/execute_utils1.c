/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:34:18 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/18 11:59:51 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int contar_total_strings(t_ast *ast) 
{
    t_ast *temp;
    int total;

    total = 0;
    temp = ast;
    while (temp->token->type <= 3) 
    {
        if (temp->token->cmd) 
        {
            for (int i = 0; temp->token->cmd[i]; i++)
            {
                total++;
            }
        }
        temp = temp->right; // Avança para o próximo nó
    }
    return total;
}

int count_array(char **arr)
{
    int i;

    i = 0;
    while(arr[i])
       i++;
	printf("said\n");
    return i;
}

// Função principal para concatenar arrays de strings de ast->cmd
char **collect_commands_redirs(t_minishell *minishell, t_ast *ast) 
{
    (void)minishell;
    int total_strings = contar_total_strings(ast);
    if (total_strings != 0)
    {
        char **resultado = malloc((total_strings + 1) * sizeof(char *)); // Aloca espaço para o resultado
        if (!resultado)
            return NULL;
        int index = 0;
        if (ast->token->dq == 1 && ft_count_words(ast->token->str) > 1)
        {
            minishell->_str_ = 1;
        }
        while (ast) 
        {
            if (ast->token->cmd)
            {
                for (int i = 0; ast->token->cmd[i]; i++) {
                    resultado[index] = strdup(ast->token->cmd[i]); // Copia cada string do array atual
                    if (!resultado[index]) {
                        // Libera memória em caso de falha
                        while (index > 0)
                            free(resultado[--index]);
                        free(resultado);
                        return NULL;
                    }
                    index++;
                }
            }
            open_file(minishell, ast);
            ast = ast->right; // Avança para o próximo nó
        }
        resultado[index] = NULL; // Finaliza o array com NULL
        return resultado;
    }
    else 
    {
        while (ast->token->type <= 3)
        {
            open_file(minishell, ast);
            ast = ast->right;
        }
        return NULL;
    }
}

// char	**collect_commands_redirs(t_ast *ast, t_minishell *minishell)
// {
// 	char	**cmd;
// 	char	**temp;
// 	int		count;

// 	cmd = NULL;
// 	count = 0;
// 	while (ast && ast->token->type <= 3)
// 	{
// 		if (ast->token->cmd)
// 		{
// 			temp = cmd;
// 			cmd = malloc(sizeof(char *) * (count + 2));
// 			if (!cmd)
// 				return (NULL);
// 			for (int i = 0; i < count; i++)
// 				cmd[i] = temp[i];
// 			cmd[count] = ft_strdup(ast->token->cmd);
// 			if (!cmd[count])
// 				return (NULL);
// 			count++;
// 			cmd[count] = NULL;
// 			if (temp)
// 				free(temp);
// 		}
// 		open_file(minishell, ast);
// 		ast = ast->right;
// 	}
// 	printf("cmd 0 %s  cmd 1 %s\n", cmd[0], cmd[1]);
// 	return (cmd);
// }

char    **collect_commands(t_minishell *minishell, t_ast *ast)
{
    char	**cmd;
    char	**temp;
    int		count;

    cmd = NULL;
    count = 0;
    (void)minishell;
    if (ast->token->dq == 1 && ft_count_words(ast->token->str) > 1)
    {
        printf("entrou\n");
        minishell->_str_ = 1;
    }
    while (ast)
    {
        temp = cmd;
        cmd = malloc(sizeof(char *) * (count + 2));
        if (!cmd)
            return (NULL);
        for (int i = 0; i < count; i++)
            cmd[i] = temp[i];
        cmd[count] = ft_strdup(ast->token->str);
        if (!cmd[count])
            return (NULL);
        count++;
        cmd[count] = NULL;
        if (temp)
            free(temp);
        ast = ast->right;
    }
    return (cmd);
}
