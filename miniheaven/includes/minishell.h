/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/19 13:15:49 by mfrancis          #+#    #+#             */
/*   Updated: 2024/09/19 13:15:49 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_signal;

typedef enum s_token_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	WORD,
	STR,
	PIPE,
	NO_TYPE,
}	t_tk_tp;

typedef struct s_heredoc
{
	struct s_heredoc	*next;
	char				*delimiter;
	char				*line;
	int					fd[2];
	int					quotes;
	int					id;
}	t_heredoc;

typedef struct s_expand
{
	char	*var_name;
	char	*var_content;
	int		dq;
	int		sq;
}	t_expand;

typedef struct s_token
{
	struct s_token	*next;
	t_tk_tp			type;
	char			*str;
	char			*path;
	char			*cmd;
}	t_token;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_token			*token;
}	t_ast;

typedef struct s_minishell
{
	t_token		*tokens;
	t_ast		*ast;
	t_expand	*expander;
	t_heredoc	*heredoc;
	char		**envp;
	char		**local;
	char		*display;
	char		*cmd;
	int			first;
	int			fd[2];
	int			exit_status;
	int			temp_stdin;
	int			temp_stdout;
	int			infile;
	int			outfile;
	int			commands;
	int			_pipe_;
	int			nbr_heredoc;
}	t_minishell;

// signals
void	setup_signals(void);
void	stop_signals(void);
void	setup_signals_here(void);
void	setup_signals_executer(void);


void	free_exit(t_minishell *minishell, char *str);
void	free_all(t_minishell *minishell, char *str);
void	free_array(char **array);
void	free_tokens(t_minishell *minishell);
void	free_expand(t_expand *expander);
void	free_ast(t_ast *ast);
void	free_heredoc(t_heredoc *heredoc);
void	fd_clean(void);

// Display Prompt
void	display_prompt(t_minishell *minishell);
void	process_input(t_minishell *minishell);

// tokanization
void	tokenization(t_minishell *minishell);
int		check_quotes(char quote, t_minishell *minishell, int *idx);
int		process_quotes(t_minishell *minishell, int *idx, char symb);

// tokenization_utils
void	process_op_tokens(t_minishell *minishell, int *start, int *idx);
void	add_operator_word(t_minishell *minishell,
			int *start, int idx, int token_type);
void	add_word(t_minishell *minishell, int *start, int *idx);
void	add_simple_token(t_minishell *minishell, int *start, int *idx);
void	add_token_back(t_minishell *minishell, char *token, t_tk_tp type);

// syntax_error
bool	check_syntax(t_token *tokens);
bool	check_syntax_pipe(t_token *temp, t_token *last_token);
bool	check_syntax_redir(t_token *temp);

// expander
void	expander(t_minishell *minishell);
int		verify_quotes(char *str, int idx, char quotes); // Necessario?
void	reset_expand(t_expand *expander);
char	*add_char(int c, char *str);
char	*extrat_var_content(t_minishell *minishell);
char	*replace_var_in_str(char *str, t_minishell *minishell, int *idx);
void	expand_vars(t_minishell *minishell, t_token *token);

// split_token
void	split_tokens(t_minishell *minishell, t_token **current);
void	add_token_between(t_minishell *minishell, t_token *tokens, char *str);
int		ft_count_words(char const *s);
int		is_delimiter(char c);
int		find_last_delimiter(char *str);

// remove_quotes
void	rm_single_quotes(t_token *token, t_minishell *minishell, int *idx);
void	rm_double_quote(t_token *token, t_minishell *minishell, int *idx);

// ast
t_tk_tp	check_redir(t_token *tokens);
int		check_symbol(t_token *tokens, t_tk_tp symbol);
t_ast	*create_ast(t_token *tokens);
t_ast	*split_tokens_ast(t_token **tokens, t_tk_tp symbol);
t_ast	*add_right(t_token **tokens);
t_ast	*split_tokens_ast(t_token **tokens, t_tk_tp symbol);
t_ast	*new_ast_node(t_token *tokens);

// heredoc
void	process_ast_heredoc(t_minishell *minishell, t_ast *ast, t_ast *head);
void	process_heredoc(t_minishell *minishell, t_ast *ast, t_ast *top);
void	process_prompt(t_minishell *minishell, t_heredoc *heredoc, t_ast *top);
void	write_to_pipe(t_minishell *minishell, t_heredoc *heredoc);

void	heredoc_quotes(t_minishell *minishell, t_heredoc *heredoc);
void	reset_heredoc(t_heredoc *heredoc);
void	rm_here_quotes(t_minishell *minishell, t_heredoc *heredoc, int *idx,
			char quote);

void heredoc_quotes(t_minishell * minishell, t_heredoc *heredoc);
void reset_heredoc(t_heredoc *heredoc);
void rm_here_quotes(t_minishell *minishell, t_heredoc *heredoc, int *idx, char quote);

//heredoc_utils
t_heredoc	*add_heredoc_node(t_minishell *minishell);
char *expand_heredoc(t_minishell *minishell, char * line);

// debug functions
void	print_token(t_minishell *data);
void	print_token2(t_token *data);
// char	*test (char *str);
void	print_ast(t_ast *ast, int level);
char	*token_type_to_str(t_tk_tp type);
void	print_heredoc(t_minishell *data);

// Built_ins //
// CD_UTILS //
char	*rebuild_pwd(char **split_pwd);
int		change_old_path(t_minishell *minishell, char *new_path);
int		change_pwd(t_minishell *minishell, char *new_path);

// CD //
void	ft_cd(char **split_cmd, t_minishell *minishell);

// ECHO //
void	ft_echo(char *str);

// ENV //
void	ft_env(t_minishell *minishell);

// EXPORT//
int		check_var(char *var, t_minishell *minishell);
void	add_var(t_minishell *minishell, char *var);
void	ft_export(t_minishell *minishell);
int	find_equal(char *var);
int	add_local(t_minishell *minishell, char *var);
int	bigger_var_name(char *original, char *step_ahead);

// PWD //
void	ft_pwd(t_minishell *minishell);

// UNSET //
void	ft_unset(char **split_cmd, t_minishell *minishell);

// Built_ins_utils //
char	**dup_envp(t_minishell *minishell, char **envp); /*Usado no export*/
char	*find_path(t_minishell *minishell, char *cmd); /*Usado no env*/

// EXECUTOR //
void	execute_ast(t_minishell *minishell, t_ast *ast, int flag);
char	*remove_equal(char *path);
char	*my_getenv(t_minishell *minishell, char *path);
int		find_builtin(t_minishell *minishell, char **dp, char *cmd);
void	error_execute(t_minishell *minishell, char **split_cmd, char *cmd_path,
			char *cmd);
void	ft_execute(t_minishell *minishell, char *cmd);
void	execute_cmd(t_minishell *minishell, char **split_cmd, char *cmd);
char	*built_cmd(t_ast *ast);

// PIPEX //
void	do_pipeline(t_minishell *minishell, t_ast *ast);
void	pipe_fork(t_minishell *minishell, t_ast *ast);
void	fork_and_pipe(t_minishell *minishell, t_ast *ast, int *child);
void	redir_pipe(t_minishell *minishell, int child);
void	wait_pipes(t_minishell *minishell);
void	ft_execute_pipe(t_minishell *minishell, char *cmd);

//	REDIR  //
int		open_file(t_minishell *minishell, t_ast *ast);
int		redirect_read(t_minishell *minishell);
void	close_redir(t_minishell *minishell);
int		rebuild_fileno(t_minishell *minishell);

//	ASSOCIATE REDIR	//
void	set_redirs(t_minishell *minishell, t_ast *ast);
void	redir_in(t_minishell *minishell, t_ast *ast, int flag);
void	redir_out(t_minishell *minishell, t_ast *ast, int flag);

void	setup_signals_executer(void);
void	free_cmd_path(t_ast *left_side);

void	do_one_pipe(t_minishell *minishell, t_ast *ast);
#endif