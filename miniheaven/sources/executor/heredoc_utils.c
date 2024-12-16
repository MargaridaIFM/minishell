/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:23:06 by mfrancis          #+#    #+#             */
/*   Updated: 2024/12/05 15:08:59 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_heredoc	*add_heredoc_node(t_minishell *minishell)
{
	t_heredoc	*new_node;
	t_heredoc	*temp;

	new_node = malloc(sizeof(t_heredoc));
	if (!new_node)
		free_exit(minishell, "Error - Fail allocating heredoc\n");
	new_node->delimiter = NULL;
	new_node->fd[0] = -1;
	new_node->fd[1] = -1;
	new_node->quotes = 0;
	new_node->id = -1;
	new_node->next = NULL;
	if (!minishell->heredoc)
		minishell->heredoc = new_node;
	else
	{
		temp = minishell->heredoc;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (new_node);
}
char *expand_heredoc(t_minishell *minishell, char * line)
{
	int i;
	char *new_str;

	i = 0;
	new_str = line;
  	if (minishell->expander == NULL) {
        minishell->expander = malloc(sizeof(t_expand));
    if (!minishell->expander)
        free_exit(minishell, "Error - Fail allocating expander");
    }
    reset_expand(minishell->expander);
	while (line[i])
	{
		if(line[i] == '$')
		{
			i++;
			if (line[i] == '?')
			{
                minishell->expander->var_name = ft_strdup("?"); // ? ($?) Expands to the exit status of the most recently executed foreground pipeline. 
				i++;
			}
			else if (!ft_isalpha(line[i]) && line[i]!= '_')
            {
                minishell->expander->var_name = add_char(line[i],  minishell->expander->var_name);
                i++;
            }
            else
            {
                while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
                {
                    minishell->expander->var_name = add_char(line[i],  minishell->expander->var_name);
					i++;
                }
            }
			minishell->expander->var_content = extrat_var_content(minishell);
			i = i - ft_strlen(minishell->expander->var_name) - 1;
            new_str = replace_var_in_str(line, minishell, &i);
            free(line);
            line = new_str;
			free_expand(minishell->expander);
		}
		i++;
	}
	return(new_str);
}