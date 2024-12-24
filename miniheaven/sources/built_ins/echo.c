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
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] && str[i] == c)
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
static int	skip(char **cmd, int *flag)
{
	int	i;

	i = 1;
	if (ft_strlen(cmd[i]) >= 2)
	{
		while (ft_strlen(cmd[i]) > 0 && find_char(cmd[i] + 1, 'n') == 1)
		{
			*flag = 1;
			i++;
		}
	}
	if (*flag == 1)
		return (i);
	return (i);
}

/**
 * @brief Vai imprimir a 'str' que recebe
 * @param char *str
 * @return (void);
 */
void	ft_echo(char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	if (cmd[1])
	{
		i = skip(cmd, &flag);
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
			if (cmd[i])
				printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}
