/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:21:23 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/04 16:29:16 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void process_ast_heredoc(t_minishell *minishell, t_ast *ast, t_ast *head)
{ 
    t_ast *temp;
	t_ast *top;

    top = head;
    temp = ast;
	//printf("entrou ast_heredoc\n");
    if (ast == NULL)
		 return;
    if(temp->token->type == REDIR_HEREDOC)
    {
        process_heredoc(minishell, temp, top);
    }  
    process_ast_heredoc(minishell, temp->left, top);
    process_ast_heredoc(minishell, temp->right, top);
}

void process_heredoc(t_minishell *minishell, t_ast *ast, t_ast *top)
{ 
    // signals do heredoc
	t_heredoc *temp;
	
	temp = add_heredoc_node(minishell);
    temp->delimiter = ft_strdup(ast->token->path);
    heredoc_quotes(minishell, temp);
	//printf("delimeter: %s\n", temp->delimiter);
	//printf("delimeter: %s\n", temp->delimiter);
	//printf("delimeter: %s\n", minishell->ast->token->str);
	//print_heredoc(minishell);
    if(pipe(temp->fd) == -1)
        free_exit(minishell, "Error - Fail creating pipe\n");
    temp->id = fork();
    if(temp->id == -1)
	{
        free_exit(minishell, "Error - Fail creating fork\n");
	}
	process_prompt(minishell, temp, top);
	
}

void process_prompt(t_minishell *minishell, t_heredoc *heredoc, t_ast *top)
{
    if(heredoc->id == 0)
    {
        // child process
        setup_signals_here();
        close(heredoc->fd[0]);
        write_to_pipe(minishell, heredoc);
        close(heredoc->fd[1]);
        while (top->token->type == PIPE)
        {
            free_cmd_path(top->left);
            top = top->right;
        }
        free_cmd_path(top);
		//free_paths(top);
        free_exit(minishell, "");
    }
    close(heredoc->fd[1]);
	waitpid(heredoc->id, &minishell->exit_status, 0);
    printf("Exit status -> %d %d %d\n", minishell->exit_status, WEXITSTATUS(minishell->exit_status), WTERMSIG(minishell->exit_status));
    minishell->exit_status =  WEXITSTATUS(minishell->exit_status);
    if (minishell->exit_status == 130)
        g_signal = 130;
    
}
	
void write_to_pipe(t_minishell *minishell, t_heredoc *heredoc)
{
    char *new_line;
	(void)minishell;
	(void)heredoc;
    
    while(1)
    {
        if(g_signal == 130)
        {
            close(heredoc->fd[1]);
            break;
        }
        new_line = readline("> ");
        if (!new_line) // CTRL+D ou erro
        {
            // g_signal = 130; //??
            close(heredoc->fd[1]);
            break;
        }
        if(ft_strcmp(new_line, heredoc->delimiter) == 0)
        {
           free(new_line);
           break;
        }
       	if(heredoc->quotes == 0)
		{

            new_line = expand_heredoc(minishell, new_line);
		}
		//printf("%s \n", new_line);
        ft_putendl_fd(new_line, heredoc->fd[1]);
        free(new_line);
	}
}

void write_to_pipe_2(t_minishell *minishell, t_heredoc *heredoc)
{
    char *new_line;
	(void)minishell;
    char *temp;

    while(1)
    {
        new_line = readline("> ");
        if(!new_line)
            break;
        if(ft_strcmp(new_line, heredoc->delimiter) == 0)
        {
           free(new_line);
           break;
        }
        temp = ft_strjoin(new_line, "\n");
        free(new_line);
        new_line = temp;
        if(heredoc->line)
        {
            temp = ft_strjoin(heredoc->line, new_line); 
            free(heredoc->line);
            heredoc->line = temp;
   		 }
        write(heredoc->fd[1], heredoc->line, ft_strlen(heredoc->line));
	//printf("temp %s\n", temp);
	free(temp);
    }
}

void heredoc_quotes(t_minishell * minishell, t_heredoc *heredoc)
{
    int idx;

    idx = 0;
    while(heredoc->delimiter[idx])
    {
        if(heredoc->delimiter[idx] == '\'')
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

void reset_heredoc(t_heredoc *heredoc)
{
    heredoc->delimiter = NULL;
    heredoc->line = NULL;
    heredoc->fd[0] = -1;  // confirmar
    heredoc->fd[1] = -1;  //  confirmar
    heredoc->quotes = 0;
    // heredoc->status = 0; ?
}		

void rm_here_quotes(t_minishell *minishell, t_heredoc *heredoc, int *idx, char quote)
{
    int start;
    int end;
    char *new_str;
    int new_idx;

    start = *idx + 1;
    end = start;
    new_idx = 0;
    while(heredoc->delimiter[end] != quote)
        end++;
    new_str = malloc(sizeof(char) * (ft_strlen(heredoc->delimiter) - 1));
    if (!new_str)
        free_exit(minishell, "Error - Fail allocating memory for new str\n");    
    ft_memcpy(new_str, heredoc->delimiter, start - 1); // primeira parte
    new_idx  = start - 1;
    ft_memcpy(new_str + new_idx, heredoc->delimiter + start, end - start); // dentro das quotes
    new_idx = new_idx + (end - start);
    ft_memcpy(new_str + new_idx, heredoc->delimiter + end + 1, (ft_strlen(heredoc->delimiter + end + 1) + 1));
    free(heredoc->delimiter);
    heredoc->delimiter = new_str;  
    *(idx) =  new_idx - 1;
}

// ! strut encadeada para os heredocs ou basta apenas ums struct processar e depois limpar?
// ! wextitstatus - pesquisar e falar com a melhor parceira do mundo 

// while(wait(NULL) != -1 || errno != ECHILD)

// fd[0] = read;
// fd[1] = write;
// proteger o fork, if fork == -1 , return erro; 
// proteger o  write e o read contra erros if (...) = -1 return erro;

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
//              [] expandir as variaveis todas( sem excepcoes de quotes) dentro do ficheiro temporario
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