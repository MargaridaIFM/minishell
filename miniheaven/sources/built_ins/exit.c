/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:59:21 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/27 12:59:21 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			print_errors("bash: exit: ", str, ": numeric argument required\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	get_exit_code(char *str)
{
	int	code;

	code = ft_atoi(str);
	if (check_number(str) == 1)
		return (2);
	return (code);
}

void	ft_exit(t_minishell *minishell, char **dp)
{
	if (count_array(dp) > 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_signal = 1;
		return ;
	}
	if (dp[1])
		g_signal = get_exit_code(dp[1]);
	free_array(dp);
	free_exit(minishell, "");
}
