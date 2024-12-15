/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:37:16 by mistery576        #+#    #+#             */
/*   Updated: 2024/10/29 17:03:58 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Imprime a variavel PWD
 * @param t_minishell *minishell
 * @return (void);
 */
void	ft_pwd(t_minishell *minishell)
{
	char	*pwd;

	pwd = my_getenv(minishell, "PWD");
	if (!pwd)
	{
		printf("Error - No PWD\n");
		exit(0);
	}
	printf("%s\n", pwd);
}
