/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:39:13 by mistery576        #+#    #+#             */
/*   Updated: 2024/09/26 17:08:39 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_char(char *str, char c)
{
	int i;

	i = 0;
	while(str[i] && str[i] == c)
		i++;
	if (!str[i])
		return (1);
	return (0);
}

/**
 * @brief Vou dar skip no 'echo' e no '-n', caso tenha o '-n', ativar a flag.
 * @param char *str, int *flag.
 * @return (int);
 */
static t_ast	*skip(t_ast *ast, int *flag)
{
	t_ast *temp;
	int i;

	temp = ast;
	i = 2;
	while(find_char(ast->token->str + 1, 'n') == 1 )
	{
		*flag = 1;
		ast = ast->right;
	}
	if (*flag == 1)
		return (ast);
	return (temp);
}

// /**
//  * @brief Vai permitir imprimir espacos enquanto nao encontrar o sinal ( " || ' )
//  * @param char *sign, char *str
//  * @return (int);
//  */
// static int	print_space(char sign, char *str)
// {
// 	int	i;

// 	i = 0;
// 	i++;
// 	while (str[i] != sign)
// 	{
// 		printf("%c", str[i]);
// 		i++;
// 	}
// 	i++;
// 	return (i);
// }

// /**
//  * @brief Vou printar a str, mas sem os espacos
//  * @param char *str.
//  * @return (int);
//  */
// static int	print_no_space(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && (str[i] != '\'' || str[i] != '"'))
// 	{
// 		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
// 		{
// 			printf("%c", str[i]);
// 			while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
// 				i++;
// 			return (i);
// 		}
// 		printf("%c", str[i]);
// 		i++;
// 	}
// 	return (i);
// }

/**
 * @brief Vai imprimir a 'str' que recebe
 * @param char *str
 * @return (void);
 */
void	ft_echo(t_minishell *minishell)
{
	t_ast *ast;

	if (minishell->ast->right)
		ast = minishell->ast->right;
	else
		return ;
	int	flag;

	flag = 0;
	ast = skip(ast, &flag);
	while (ast)
	{
		printf("%s", ast->token->str);
		if (ast->right)
			printf(" ");
		ast = ast->right;
	}
	if (flag == 0)
		printf("\n");
}
