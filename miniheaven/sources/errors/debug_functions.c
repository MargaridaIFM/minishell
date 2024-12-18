/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:41:40 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/13 09:45:52 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_token(t_minishell *data)
{
	t_token	*current;
	int		i;

	i = 0;
	current = data->tokens;
	if (current == NULL)
	{
		ft_printf("A lista A está vazia.\n");
		return ;
	}
	while (current)
	{
		ft_printf("i: %d \n str: %s \n enum: %d \n ", i, current->str,
			current->type);
		current = current->next;
		i++;
	}
	if (data->tokens->next == NULL)
		ft_printf("NULL\n");
}
void	print_token2(t_token *data)
{
	t_token	*current;
	int		i;

	i = 0;
	current = data;
	if (current == NULL)
	{
		ft_printf("A lista A está vazia.\n");
		return ;
	}
	while (current)
	{
		ft_printf("i: %d \n str: %s \n enum: %d \n ", i, current->str,
			current->type);
		current = current->next;
		i++;
	}
	if (data->next == NULL)
		ft_printf("NULL\n");
}

void	print_ast(t_ast *ast, int level)
{
	int		idx;
	//char	*str;

	idx = 0;
	if (ast == NULL)
		return ;
	while (idx < level)
	{
		ft_printf("    ");
		idx++;
	}
	//str = token_type_to_str(ast->token->type);
	//id (str)
	if (ast->token->type <= 3)
	{
		if (ast->token->cmd)
			printf("(BRUH: %s file associated %s  comand %s)\n", ast->token->str, ast->token->path, ast->token->cmd[0]);
		else
			printf("(BRUH: %s file associated %s)\n", ast->token->str, ast->token->path);
	}
	else
		printf("(BRUH: %s file associated %s)\n", ast->token->str, ast->token->path);
	if (ast->left != NULL)
		print_ast(ast->left, level + 1);
	if (ast->right != NULL)
		print_ast(ast->right, level + 1);
}

char	*token_type_to_str(t_tk_tp type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (type == REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	else if (type == WORD )
		return ("WORD");
	else if (type == STR )
		return ("STR");
	else
		return ("UNKNOWN");
}
// int verify_quotes(char *str, int idx, char quotes)
// {
//     idx++;
//     if (quotes == '\'')
//     {
//         while(str[idx] != quotes)
//             idx++;
//         return(idx);
//     }
//     return(idx);
// }

void	print_heredoc(t_minishell *data)
{
	t_heredoc	*current;

	current = data->heredoc;
	if (current == NULL)
	{
		ft_printf("A lista A está vazia.\n");
		return ;
	}
	while (current)
	{
		ft_printf("id: %d \n delitimer: %s \n fd[0]: %d \n fd[1]: %d quotes: %d \n ", current->id,
			current->delimiter, current->fd[0], current->fd[1], current->quotes);
		current = current->next;
		
	}
	if (data->heredoc->next == NULL)
		ft_printf("NULL\n");
}