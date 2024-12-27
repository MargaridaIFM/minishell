/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:33:05 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/16 14:33:05 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

static void	update_lvl(t_minishell *minishell, char *envp, int start)
{
	char	*new_lvl;
	int		lvl;

	minishell->envp[start] = NULL;
	lvl = ft_atoi(envp + 6) + 1;
	new_lvl = ft_itoa(lvl);
	minishell->envp[start] = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
}

static int	create_env(t_minishell *minishell, char *envp[], int envp_counter)
{
	int	i;

	i = 0;
	while (i < envp_counter)
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			update_lvl(minishell, envp[i], i);
		else
			minishell->envp[i] = ft_strdup(envp[i]);
		if (!minishell->envp[i])
			free_exit(minishell, "Error - Memory envp fail\n");
		i++;
	}
	if (envp_counter < 3)
	{
		i = 3;
	}
	return (i);
}

static void	mandatory_env(t_minishell *minishell)
{
	char	*pwd;
	char	*shlvl;
	char	*oldpwd;

	if (my_getenv(minishell, "PWD") == NULL)
	{
		pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
		minishell->envp = add_string_to_array(minishell->envp, pwd);
		free(pwd);
	}
	if (my_getenv(minishell, "OLDPWD") == NULL)
	{
		oldpwd = ft_strdup("OLDPWD");
		minishell->envp = add_string_to_array(minishell->envp, oldpwd);
		free(oldpwd);
	}
	if (my_getenv(minishell, "SHLVL") == NULL)
	{
		shlvl = ft_strdup("SHLVL=1");
		minishell->envp = add_string_to_array(minishell->envp, shlvl);
		free(shlvl);
	}
}

static void	initialization(char *envp[], t_minishell *minishell)
{
	int	envp_counter;
	int	i;

	envp_counter = 0;
	i = 0;
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->local = malloc(sizeof(char *) * 1);
	minishell->local[0] = NULL;
	minishell->_str_ = 0;
	minishell->_pipe_ = 0;
	minishell->temp_stdin = -1;
	minishell->temp_stdout = -1;
	minishell->infile = -1;
	minishell->outfile = -1;
	minishell->tokens = NULL;
	while (envp[envp_counter])
		envp_counter++;
	minishell->envp = malloc(sizeof(char *) * (envp_counter + 1));
	if (!minishell->envp)
		free_exit(minishell, "Error - Memory allocation fail\n");
	i = create_env(minishell, envp, envp_counter);
	mandatory_env(minishell);
	minishell->envp[i] = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	(void)argv;
	if (argc != 1)
		exit(0);
	initialization(envp, &minishell);
	while (1)
	{
		setup_signals();
		display_prompt(&minishell);
	}
	free_exit(&minishell, "");
	return (0);
}

/*
			[/] Inicialization of data/ minishell;
				[/] structs
				[x] envp
				[x] SHLVL
			[/] setup_signals
				[x]  crtl D
				[x]  crtl \
				[x]  crtl C
				[] consider child process;
			[?] display_prompt - rl_redisplay minishell$
				[x] ver leaks - suprimir - supression file - .supp
			[] ler input  - readline ?
				[] Lexing
					[] token
						[x] funcao gettoken
							[x] incrementaro o idx ate encontrar um dos simbolos
								[x] se encontra > ou < ver se tem outro a seguir
									e dar outro tipo de char ?
							[x] split split da palavra se tiver antes do simbolo
							[x] split do simbolo
							[x] trim p limpar os withespaces;
				[] Parser
					[] BNF (apenas um doc para mim p conseguir fazer o sintax 
					error)
					'--> [] Error sintax
							'--> [] AST
				[/] execution
					[/] build-in or system ?
						[x]  pwd (Finito,
							e sem memory leaks e sem erros de norma)
						[x]  cd (Finito,
							e sem memory leaks e sem erros de norma)
							[x] Corrigir o bug,
								quando estou no dir '/' e ando para outro 
								diretorio,
								o output é '//home'
						[x]  env (Finito,
							e sem memory leaks e sem erros de norma)
						[x]  export (Finito,
							e sem memory leaks e sem erros de norma)
							[x] Não pode aceitar variaveis com numeros
							[x] Dar export de local variables

						[/]  echo -n (Sem memory leaks,
							norma falta o header. Falta considerar algumas 
							condicoes)
						[x]  unset (Finito,
							e sem memory leaks e sem erros de norma)
						[x]  exit (Finito,
							fiz o reaproveitamento da funcao que ja existe)
			[x] free(input);
			[x] Executor;
				[x] Documentacao (Finito)
				[x] Aceitar os comandos a partir do diretorio, por exemplo
					/bin/ls
			[x] CORRIGIR PIPEX;
				[x] Caso nao exista o infile,
					mas ja existe informacao no outfile,
					tenho de limpar quando ex (infile ls wc outfile)
				[] Adicionar a funcionalidade "here_doc"
				[] Caso o numero de argumentos esteja errado no here_doc,
					a mensagem de erro aparece dentro do outfile
			[] LOCAL VARIABLES
				[x] Adicionar uma variavel local, à minha lista
				[x] Verificar se já existe a variavel local
					[x] Caso exista, tenho de alterar o content da varável
				[x] Comportar-se com export
				[x] Comportar-se com unset
				[x] Verificar se a variavel ja existe no envp
				[] Dar erro quando teste=" ou teste='
				[] Caso faça teste=! e dps eu fizer export teste=1,
					tenho de tirar da local_var e exportar com o novo valor
				OUTPUTS ESTRANHOS
					[] test= | A variavel fica com o valor nulo
					[x] unset teste | A função unset tb funciona para variaveis 
					locais
			[x] Alterar o Shell level, quando executamos outra vez o minishell
			[x] Aceitar comandos como por exemplo "ls -l"

			PENDÊNCIAS
			[] Variaveis locais com aspas

			MIGUEL CORRIGIR HOJE:
			[] export
				[] a="ls -l -a"
*/
