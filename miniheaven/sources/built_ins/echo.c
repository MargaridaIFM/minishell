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

/**
 * @brief Vou dar skip no 'echo' e no '-n', caso tenha o '-n', ativar a flag.
 * @param char *str, int *flag.
 * @return (int);
 */
static int	skip(char *str, int *flag)
{
	char	**split_str;
	int		i;

	i = 0;
	split_str = ft_split(str, ' ');
	if (ft_strcmp(split_str[1], "-n") == 0)
		*flag = 1;
	while (str[i] != 'o')
		i++;
	if (*flag == 1)
	{
		while (str[i] != 'n')
			i++;
	}
	i++;
	free_array(split_str);
	return (i);
}

/**
 * @brief Vai permitir imprimir espacos enquanto nao encontrar o sinal ( " || ' )
 * @param char *sign, char *str
 * @return (int);
 */
static int	print_space(char sign, char *str)
{
	int	i;

	i = 0;
	i++;
	while (str[i] != sign)
	{
		printf("%c", str[i]);
		i++;
	}
	i++;
	return (i);
}

/**
 * @brief Vou printar a str, mas sem os espacos
 * @param char *str.
 * @return (int);
 */
static int	print_no_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != '\'' || str[i] != '"'))
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		{
			printf("%c", str[i]);
			while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
				i++;
			return (i);
		}
		printf("%c", str[i]);
		i++;
	}
	return (i);
}

/**
 * @brief Vai imprimir a 'str' que recebe
 * @param char *str
 * @return (void);
 */
void	ft_echo(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = skip(str, &flag);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'' )
			i += print_space(str[i], str + i);
		else
			i += print_no_space(str + i);
	}
	if (flag == 0)
		printf("\n");
}
