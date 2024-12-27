/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:35:32 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/16 14:35:32 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_prompt(t_minishell *minishell)
{
	if (g_signal != 0)
	{
		minishell->exit_status = g_signal;
		g_signal = 0;
	}
	if (!minishell->display)
		minishell->display = readline("[minishell]$ ");
	if (!minishell->display)
		free_exit(minishell, "");
	if (!*minishell->display)
	{
		free_all(minishell, "");
		return ;
	}
	add_history(minishell->display);
	process_input(minishell);
	free_all(minishell, "");
}

void	process_util(t_minishell *minishell, t_ast *ast)
{
	if (minishell->nbr_heredoc > 0)
	{
		process_ast_heredoc(minishell, minishell->ast, minishell->ast);
		minishell->nbr_heredoc = 0;
	}
	if (g_signal)
	{
		free_ast(minishell->ast);
		minishell->ast = NULL;
	}
	else
	{
		minishell->first = 0;
		setup_signals_executer();
		execute_ast(minishell, ast, -1);
		free_ast(minishell->ast);
		minishell->ast = NULL;
	}
}

void	check_is_str(t_minishell *minishell)
{
	t_token	*temp;
	int		flag;

	flag = 0;
	temp = minishell->tokens;
	while (temp)
	{
		if (temp->str[0] == '"' && flag == 0)
		{
			temp->dq = 1;
			flag = 1;
		}
		else
			temp->dq = 0;
		if (temp->type == PIPE)
			flag = 0;
		temp = temp->next;
	}
}

void	process_input(t_minishell *minishell)
{
	t_ast	*ast;

	stop_signals();
	tokenization(minishell);
	check_is_str(minishell);
	if (check_syntax(minishell->tokens) == true)
	{
		expander(minishell);
		minishell->ast = create_ast(minishell->tokens);
		ast = minishell->ast;
		if (!minishell->ast)
			return ;
		minishell->tokens = NULL;
		set_redirs(minishell, minishell->ast);
		process_util(minishell, ast);
	}
	else
	{
		g_signal = 2;
		return ;
	}
}

/* EM FALTA:
	[/] expander
		[x] onde faco
		[x] exemplo do ls -l
		[] verificar se vou buscar ao getenv;
		[] variaveis locais;
	[/] remove quotes
	[] split token
	[x] testar ast
	[] correr ast
		[] heredoc cat << EOF
	[] signals
*/
// teste: cat file.txt |ls | grep "example" > output.txt

/*
	[]execute_ast
		[] if ast == word
			[] execute_cmd - build in
		[] if ast == PIPE
			[] cria pipe
			[] fork esquerda
				[]execute_ast
			[] if (ast->rigth == PIPE
				[] skip
			[] else if  != PIPE
				[] fork direita
			// 	[] execute_ast
		// []if ast == REDIR
		// 	[] handle_redir
		// 	[] execute_ast

 */