/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:31:38 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/14 11:26:42 by mfrancis         ###   ########.fr       */
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
		return free_all(minishell, "");
	add_history(minishell->display); // Verificar o caso < infile cat > outfile e depois andar para tras e frente --> come o 'ell' do 'minishell'
	process_input(minishell);
	free_all(minishell, "");
}

void	process_input(t_minishell *minishell)
{
	//int teste;
	stop_signals();
	tokenization(minishell);
	if (check_syntax(minishell->tokens) == true)
	{
		expander(minishell);
		minishell->ast = create_ast(minishell->tokens);
		if(!minishell->ast)
			return ;
		minishell->tokens = NULL;
		set_redirs(minishell, minishell->ast);
		if(minishell->nbr_heredoc > 0)
		{
			process_ast_heredoc(minishell, minishell->ast, minishell->ast);
			minishell->nbr_heredoc = 0;
		}
		minishell->first = 0;
		//print_ast(minishell->ast, 0);
		//print_env(minishell, "ANTES EXECUCAO");
		//ligar sinais do executer dentro da execute_ast;
		execute_ast(minishell, minishell->ast, -1);
		free_ast(minishell->ast);
		// teste = open("infile", O_RDONLY);
		// printf("teste %d\n", teste);
		//close(teste);
		minishell->ast = NULL;
	}
	else
	{
		//g_signal = 2;
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