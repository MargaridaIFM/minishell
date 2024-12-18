/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:54:50 by mfrancis          #+#    #+#             */
/*   Updated: 2024/10/30 18:01:47 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

// void	free_exit(t_minishell *minishell, char *str)
// {
// 	if (str && str[0] != '\0')
// 		ft_putstr_fd(str, 2);
// 	if (minishell->envp)
// 		free_array(minishell->envp);
// 	if (minishell->display)
// 		free(minishell->display);
	
// 	if(minishell->expander)
// 	{
// 		free_expand(minishell->expander);
// 		free(minishell->expander);
//         minishell->expander = NULL;
// 	}
	
// 	if (minishell->tokens)
// 		free_tokens(minishell);
// 	if(minishell->ast)
// 	{
// 		free_ast(minishell->ast);
// 		minishell->ast = NULL;		
// 	}
// 	if (minishell->temp_stdin != -1)
// 		close (minishell->temp_stdin);
// 	if (minishell->temp_stdout != -1)
// 		close (minishell->temp_stdout);
// 	if (minishell->fd[1] > 0)
// 		close(1);
// 	if (minishell->fd[0] > 0)
// 		close(0);
// 	if(minishell->cmd)
// 	{
// 		free(minishell->cmd);
// 		minishell->cmd = NULL;
// 	}
// 	if (minishell->heredoc)
// 	{
// 		free_heredoc(minishell->heredoc);
//     	// free(minishell->heredoc);
//    		minishell->heredoc = NULL;
// 	}
	
// 	if (minishell->temp_stdin != -1)
// 		close(0);
// 	if (minishell->temp_stdout != -1)
// 		close(1);
// 	fd_clean();
// 	//printf("File descriptor %d   %d\n", minishell->fd[0], minishell->fd[1]);
// 	exit(0);
// }

// void	free_all(t_minishell *minishell, char *str)
// {
// 	if (str && str[0] != '\0')
// 		ft_putstr_fd(str, 2);
// 	if(minishell->ast)
// 	{
// 		free_ast(minishell->ast);
// 		minishell->ast = NULL;
// 	}
// 	if (minishell->display)
// 	{
// 		free(minishell->display);
// 		minishell->display = NULL;
// 	}
// 	if (minishell->tokens)
// 		free_tokens(minishell);
// 	if(minishell->expander)
// 	{
// 		free_expand(minishell->expander);
// 		free(minishell->expander);
//         minishell->expander = NULL;
// 	}
// 	if (minishell->heredoc)
// 	{
// 		free_heredoc(minishell->heredoc);
//     	// free(minishell->heredoc);
//    		minishell->heredoc = NULL;
// 	}
// }

void	free_array(char **array)
{
	int	idx;

	idx = 0;
	while (array[idx])
	{
		free(array[idx]);
		idx++;
	}
	free(array);
}

void	free_tokens(t_minishell *minishell)
{
	t_token	*current;
	t_token	*next;

	current = minishell->tokens;
	while (current)
	{
		if (current->next)
			next = current->next;
		else
			next = NULL;
		if (current->str)
			free(current->str);
		if (current->path)
			free(current->path);
		if (current->cmd)
			free(current->cmd);
		free(current);
		current = next;
	}
	minishell->tokens = NULL;
}

void	free_expand(t_expand *expander)
{
	if (expander != NULL)
	{
		if (expander->var_content != NULL)
		{
			free(expander->var_content);
			expander->var_content = NULL;
		}
		if (expander->var_name != NULL)
		{
			free(expander->var_name);
			expander->var_name = NULL;
		}
	}
}

void	free_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->token->type <= 3)
	{
		free(ast->token->path);
		if (ast->token->cmd)
			free_array(ast->token->cmd);
	}
	if (ast->left)
		free_ast(ast->left);
	free(ast->token->str);
	//free(ast->token->path);
	//free(ast->token->cmd);
	free(ast->token);
	if (ast->right)
		free_ast(ast->right);
	free(ast);
}

void	free_heredoc(t_heredoc *heredoc)
{
	t_heredoc *temp;
	t_heredoc	*next;

	temp = heredoc;
    while(temp)
    {
        if (temp->delimiter != NULL)
        {
            free(temp->delimiter);
            temp->delimiter = NULL;
        }
         if (temp->fd[0] != -1)  // -1 indica que não foi aberto
        {
            close(temp->fd[0]);
            temp->fd[0] = -1;  // Evita que o descritor seja fechado novamente
        }
        if (temp->fd[1] != -1)  // -1 indica que não foi aberto
        {
            close(temp->fd[1]);
            temp->fd[1] = -1;  
    	} 
		next = temp->next;
		// susbituir pela funcao fd_clean  ?;
		free(temp);
		temp = next;
	}
}

//Sugestao para o free_heredoc
// Linha 93 e linhe 96, tirei do if statement