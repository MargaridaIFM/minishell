/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:16:15 by mistery576        #+#    #+#             */
/*   Updated: 2024/10/29 16:19:56 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Compara a (char *var) com (char *env) antes do '='
 * @param char *var, char *env
 * @return (void);
 */
static int	compare_vars(char *var, char *env)
{
	int	i;

	i = 0;
	while (var[i] && env[i] && env[i] != '=')
	{
		if (var[i] != env[i])
			return (var[i] - env[i]);
		i++;
	}
	if ((!env[i] || env[i] == '=') && !var[i])
		return (0);
	return (-1);
}

/**
 * @brief Limpa a envp no endereco start
 * @param t_minishell *minishell, int start
 * @return (void);
 */
static void	clear_var(t_minishell *minishell, int start)
{
	free(minishell->envp[start]);
	minishell->envp[start] = NULL;
	while (minishell->envp[start + 1])
	{
		minishell->envp[start] = minishell->envp[start + 1];
		start++;
	}
	minishell->envp[start] = NULL;
}

/**
 * @brief Limpa as vairaveis recebidas no split_cmd
 * @param t_minishell *minishell
 * @return (void);
 */
void	ft_unset(char **split_cmd, t_minishell *minishell)
{
	int	i;
	int	x;

	i = 1;
	while (split_cmd[i])
	{
		x = 0;
		while (minishell->envp[x])
		{
			if (compare_vars(split_cmd[i], minishell->envp[x]) == 0)
				clear_var(minishell, x);
			x++;
		}
		i++;
	}
}
