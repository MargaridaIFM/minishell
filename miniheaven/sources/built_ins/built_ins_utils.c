/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:36:05 by mistery576        #+#    #+#             */
/*   Updated: 2024/10/29 17:05:46 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Usado na funcao export(), vai duplicar 
 * o envp, organizar, e retornar esse array.
 * @param char **envp;
 * @return (char **);
 */
char	**dup_envp(char **envp)
{
	char	**envp_dup;
	int		envp_counter;
	int		i;

	i = 0;
	envp_counter = 0;
	while (envp[envp_counter])
		envp_counter++;
	envp_dup = malloc(sizeof (char *) * (envp_counter + 1));
	if (!envp_dup)
	{
		printf("Failed to allocate the env_dup\n");
		free_array(envp_dup);
		return (NULL);
	}
	while (i < envp_counter)
	{
		envp_dup[i] = strdup(envp[i]);
		i++;
	}
	envp_dup[i] = NULL;
	return (envp_dup);
}

/**
 * @brief Vai procurar no **split_dir, o **split_cmd, e ver se existe o 
 * comando e se da para executar.
 * @param char *full_path, char **split_cmd, char **dir
 * @return (char **full_path);
 */
static char	*find_path_util(char *full_path, char **split_cmd, char **split_dir)
{
	int	i;

	i = 0;
	while (split_dir[i] != NULL)
	{
		full_path = ft_strjoin(split_dir[i], "/");
		full_path = ft_strjoin_gnl(full_path, split_cmd[0]);
		if (access(full_path, X_OK) == 0)
		{
			free_array(split_dir);
			free_array(split_cmd);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(split_dir);
	free_array(split_cmd);
	return (NULL);
}

/**
 * @brief Vai encontrar o PATH do comando do terminal.
 * @param char *cmd.
 * @return (char **full_path);
 */
char	*find_path(t_minishell *minishell, char *cmd)
{
	char	**split_env;
	char	**split_cmd;
	char	*full_path;
	char	*path_envp;

	path_envp = my_getenv(minishell, "PATH");
	if (path_envp == NULL)
		exit(0);
	split_env = ft_split(path_envp, ':');
	split_cmd = ft_split(cmd, ' ');
	full_path = NULL;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	else
		full_path = find_path_util(full_path, split_cmd, split_env);
	return (full_path);
}
