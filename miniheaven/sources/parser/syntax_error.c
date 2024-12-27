/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:29:23 by mfrancis          #+#    #+#             */
/*   Updated: 2024/10/22 12:09:44 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_syntax(t_token *tokens)
{
	t_token		*temp;
	t_token		*last_token;
	bool		valid;

	temp = tokens;
	last_token = NULL;
	while (temp)
	{
		valid = true;
		if (temp->type == PIPE)
			valid = check_syntax_pipe(temp, last_token);
		else if (temp->type == REDIR_IN
			|| temp->type == REDIR_HEREDOC
			|| temp->type == REDIR_OUT
			|| temp->type == REDIR_APPEND)
			valid = check_syntax_redir(temp);
		if (!valid)
			return (false);
		last_token = temp;
		temp = temp->next;
	}
	return (true);
}

bool	check_syntax_pipe(t_token *temp, t_token *last_token)
{
	if (!last_token || last_token->type != WORD)
	{
		ft_putendl_fd("Syntax error near unexpected token `|'", 2);
		return (false);
	}
	if (!temp->next || temp->next->type == PIPE)
	{
		ft_putendl_fd("Syntax error near unexpected token `|'", 2);
		return (false);
	}
	return (true);
}

bool	check_syntax_redir(t_token *temp)
{
	if (!temp->next || temp->next->type != WORD)
	{
		ft_putendl_fd("Syntax error near unexpected token", 2);
		return (false);
	}
	return (true);
}
