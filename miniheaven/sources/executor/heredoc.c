/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:47:38 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/16 14:47:38 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_ast_heredoc(t_minishell *minishell, t_ast *ast, t_ast *head)
{
	t_ast	*temp;
	t_ast	*top;

	top = head;
	temp = ast;
	if (ast == NULL)
		return ;
	if (temp->token->type == REDIR_HEREDOC)
	{
		process_heredoc(minishell, temp, top);
	}
	process_ast_heredoc(minishell, temp->left, top);
	process_ast_heredoc(minishell, temp->right, top);
}

void	process_heredoc(t_minishell *minishell, t_ast *ast, t_ast *top)
{
	t_heredoc	*temp;

	temp = add_heredoc_node(minishell);
	temp->delimiter = ft_strdup(ast->token->path);
	heredoc_quotes(minishell, temp);
	if (pipe(temp->fd) == -1)
		free_exit(minishell, "Error - Fail creating pipe\n");
	temp->id = fork();
	if (temp->id == -1)
	{
		free_exit(minishell, "Error - Fail creating fork\n");
	}
	process_prompt(minishell, temp, top);
}

void	process_prompt(t_minishell *minishell, t_heredoc *heredoc, t_ast *top)
{
	(void)top;
	if (heredoc->id == 0)
	{
		setup_signals_here();
		close(heredoc->fd[0]);
		write_to_pipe(minishell, heredoc);
		close(heredoc->fd[1]);
		free_exit(minishell, "");
	}
	close(heredoc->fd[1]);
	waitpid(heredoc->id, &minishell->exit_status, 0);
	minishell->exit_status = WEXITSTATUS(minishell->exit_status);
	if (minishell->exit_status == 130)
		g_signal = 130;
}

void	write_to_pipe(t_minishell *minishell, t_heredoc *heredoc)
{
	char	*new_line;

	while (1)
	{
		if (g_signal == 130)
		{
			close(heredoc->fd[1]);
			break ;
		}
		new_line = readline("> ");
		if (!new_line)
		{
			close(heredoc->fd[1]);
			break ;
		}
		if (ft_strcmp(new_line, heredoc->delimiter) == 0)
		{
			free(new_line);
			break ;
		}
		if (heredoc->quotes == 0)
			new_line = expand_heredoc(minishell, new_line);
		ft_putendl_fd(new_line, heredoc->fd[1]);
		free(new_line);
	}
}

void	heredoc_quotes(t_minishell *minishell, t_heredoc *heredoc)
{
	int	idx;

	idx = 0;
	while (heredoc->delimiter[idx])
	{
		if (heredoc->delimiter[idx] == '\'')
		{
			heredoc->quotes = 1;
			rm_here_quotes(minishell, heredoc, &idx, '\'');
		}
		else if (heredoc->delimiter[idx] == '"')
		{
			heredoc->quotes = 1;
			rm_here_quotes(minishell, heredoc, &idx, '"');
		}
		idx++;
	}
}

// ! strut encadeada para os heredocs ou basta apenas ums 
// ! struct processar e depois limpar?
// ! wextitstatus - pesquisar e falar com a melhor parceira do mundo

// while(wait(NULL) != -1 || errno != ECHILD)

// fd[0] = read;
// fd[1] = write;
// proteger o fork, if fork == -1 , return (erro);
// proteger o  write e o read contra erros if (...) = -1 return (erro);

// cat << $USER
// > $HOME
// > $USER
// nao expande o eof
// expande as variaveis

// sempre que tiver aspas no eof
// cat << "$USER"  ou e"of" '$user'
// > $HOME
// > $USER
// remove as aspas do eof
// nao expande o eof
// nao expande as variaveis

// [] percorrer a arvore
//  [x] nao expandir o eof - flag
//  [x] pipe
//  [x] fork
//       [x] child
//          [] write to pipe
//              [] ler o promp
//              [] ler ate encontrar o eof
//           [] se NAO aspas - flag
//              [] expandir as variaveis todas( sem excepcoes de quotes) 
//					dentro do ficheiro temporario
//              [] //TODO  NAO remove quotes
//           [] se aspas - flag
//              [] NAO expandir as variaveis
//              [] //TODO  NAO remove quotes
//        [] parent
//              [] read from pipe
//              [] waitpid;
// signals

// cat << HEREDOC1 | grep "test" | wc -l << HEREDOC2

/*
recebe 4 coisas:
	[] expander especifico heredoc
	[] como guardo os inputs\
	[] onde guardo - fd ou buffer
	[]excepcoes
		[] crd D == EOF
		[] ctl C == parar - retorno para o prompt

	strut s_heredoc
	{
		t_input
		idx_aspas;
	}

	struct s_input;
 */
