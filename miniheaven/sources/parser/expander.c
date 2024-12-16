/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:14:08 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/14 17:59:33 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	expander(t_minishell *minishell)
{
	t_token	*temp;

	temp = minishell->tokens;
	while (temp)
	{
		if (temp->type == REDIR_HEREDOC)
		{
			minishell->nbr_heredoc++;
			if (temp->next)
				temp = temp->next;
		}
		else if (temp->type == WORD)
		{
			expand_vars(minishell, temp);
			//split_tokens(minishell, &temp);
		}
		temp = temp->next;
	}
	free(minishell->expander);
	minishell->expander = NULL;
}

char	*add_char(int c, char *str)
{
	char	*new_msg;
	size_t	len;

	if (!str)
		str = ft_strdup("");
	len = ft_strlen(str);
	new_msg = malloc(sizeof(char) * (len + 2));
	if (!new_msg)
	{
		if (str)
			free(str);
		return (NULL);
	}
	ft_strlcpy(new_msg, str, len + 1);
	new_msg[len] = (char)c;
	new_msg[len + 1] = '\0';
	free(str);
	return (new_msg);
}

void	reset_expand(t_expand *expander)
{
	expander->var_content = NULL;
	expander->var_name = NULL;
	expander->dq = 0;
	expander->sq = 0;
}

char	*extrat_var_content(t_minishell *minishell)
{
	char	*str;

	str = NULL;
	if (minishell->expander->var_name == NULL)
		return (NULL);
	if (ft_strcmp(minishell->expander->var_name, "?") == 0)
	{
		str = ft_itoa(minishell->exit_status);
		return (str);
	}
	else if (my_getenv(minishell, minishell->expander->var_name) != NULL)
		str = ft_strdup(my_getenv(minishell, minishell->expander->var_name));
	return (str);
}
