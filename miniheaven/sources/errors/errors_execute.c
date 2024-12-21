/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:30:23 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/20 20:54:37 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_execute(t_minishell *minishell, char **cmd)
{
	if (my_getenv(minishell, "PATH") == NULL && access(cmd[0], X_OK) != 0)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_signal = 127;
		minishell->_str_ = 0;
		return (free_array(cmd), 1);
	}
	if (minishell->_str_ == 1)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_signal = 127;
		minishell->_str_ = 0;
		return (free_array(cmd), 1);
	}
	return (0);
}