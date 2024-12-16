/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:04:01 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/16 22:54:07 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_equal(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (0);
		i++;
	}
	return (-1);
}

char	**update_local(t_minishell *minishell, char *var, int len)
{
	char	**dup_arr;
	int		i;

	i = 0;
	dup_arr = malloc(sizeof(char *) * (len + 2));
	while (minishell->local[i])
	{
		dup_arr[i] = ft_strdup(minishell->local[i]);
		i++;
	}
	i = 0;
	while (minishell->local[i])
	{
		free(minishell->local[i]);
		i++;
	}
	free(minishell->local);
	dup_arr[i] = ft_strdup(var);
	i++;
	dup_arr[i] = NULL;
	return (dup_arr);
}

int	add_local(t_minishell *minishell, char *var)
{
	int	i;

	i = 0;
	while (minishell->local[i])
		i++;
	minishell->local = update_local(minishell, var, i);
	return (0);
}

void	check_local(t_minishell *minishell, char *var, int x)
{
	int		i;
	int		j;

	i = 0;
	while (minishell->local[i])
	{
		if (ft_strncmp(minishell->local[i], var, x) == 0)
		{
			free(minishell->local[i]);
			j = i;
			while (minishell->local[j + 1])
			{
				minishell->local[j] = minishell->local[j + 1];
				j++;
			}
			minishell->local[j] = NULL;
			return;
		}
		i++;
	}
}
