/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   740_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:01:20 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/12 12:09:55 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Finds the full path of a command.
 *
 * This function checks if the command is an absolute or relative path
 * (containing a slash). If not, it searches for the command in the directories
 * specified by the PATH environment variable.
 *
 * @param cmd The command to find (array of strings, where cmd[0] is the command
 * name).
 * @param shell The shell structure containing environment variables and exit
 * code.
 * @return The full path of the command if found, or NULL otherwise.
 */
char	*get_cmd_path(char **cmd, t_shell *shell)
{
	char	**split_paths;
	char	*env_value;
	char	*path;

	path = check_for_slash(cmd[0]);
	if (path)
		return (path);
	env_value = get_env_value(shell->env, "PATH");
	if (!env_value)
		return (NULL);
	split_paths = ft_split(env_value, ':');
	if (!split_paths)
		return (perror("malloc failed"), NULL);
	if (split_paths[0] == NULL)
		return (perror("command not found"), NULL);
	path = find_exec_path(split_paths, cmd[0]);
	ft_free_split(split_paths);
	if (!path || path[0] == '\0')
	{
		if (!path)
			return (perror("malloc failed"), NULL);
		else
			return (free(path), perror("command not found"), NULL);
	}
	return (path);
}

/**
 * @brief Checks if a command contains a slash and is executable.
 *
 * This function checks if the command is an absolute or relative path
 * (e.g., starts with '/', './', or '../') and verifies if it is executable.
 *
 * @param cmd The command to check.
 * @return A newly allocated string with the command path if executable,
 *  or NULL otherwise.
 */
char	*check_for_slash(char *cmd)
{
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

/**
 * @brief Searches for the executable path of a command in a list of directories.
 *
 * This function iterates through the directories in the split PATH environment
 * variable, appending the command to each directory and checking if the
 * resulting path is executable.
 *
 * @param split_paths Array of directories to search.
 * @param cmd The command to find.
 * @return The executable path if found, or an empty string if not found.
 */
char	*find_exec_path(char **split_paths, char *cmd)
{
	char	*path;
	char	*path_bar;
	int		i;

	i = 0;
	while (split_paths[i] != NULL)
	{
		path_bar = ft_strjoin(split_paths[i], "/");
		if (path_bar == NULL)
			return (NULL);
		path = ft_strjoin(path_bar, cmd);
		free(path_bar);
		if (path == NULL)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return ("");
}

/**
 * @brief Frees a split string array.
 *
 * This function frees all the strings in the array and the array itself.
 *
 * @param split The array of strings to free.
 */
void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
