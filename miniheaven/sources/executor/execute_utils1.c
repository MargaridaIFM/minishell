/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:34:18 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/17 00:08:35 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**collect_commands_redirs(t_ast *ast, t_minishell *minishell)
{
	char	**cmd;
	char	**temp;
	int		count;

	cmd = NULL;
	count = 0;
	while (ast && ast->token->type <= 3)
	{
		if (ast->token->cmd)
		{
			temp = cmd;
			cmd = malloc(sizeof(char *) * (count + 2));
			if (!cmd)
				return (NULL);
			for (int i = 0; i < count; i++)
				cmd[i] = temp[i];
			cmd[count] = ft_strdup(ast->token->cmd);
			if (!cmd[count])
				return (NULL);
			count++;
			cmd[count] = NULL;
			if (temp)
				free(temp);
		}
		open_file(minishell, ast);
		ast = ast->right;
	}
	return (cmd);
}

char    **collect_commands(t_ast *ast)
{
    char	**cmd;
    char	**temp;
    int		count;

    cmd = NULL;
    count = 0;

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
