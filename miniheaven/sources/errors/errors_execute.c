/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:30:23 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/23 23:54:28 by mistery576       ###   ########.fr       */
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

void	print_errors(char *s1, char *s2, char *s3)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (s3)
		ft_putstr_fd(s3, 2);
}

char	*failed_to_open(t_minishell *minishell)
{
	g_signal = 1;
	if (minishell->_pipe_ == 1)
		free_exit(minishell, "");
	return (NULL);
}
