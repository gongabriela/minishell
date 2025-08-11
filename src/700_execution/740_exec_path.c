/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   740_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:01:20 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/11 16:19:52 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*get_cmd_path(char **cmd, t_shell *shell)
{
	char	**split_paths;
	char	*env_value;
	char	*path;

	if (cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2) == 0
		|| ft_strncmp(cmd[0], "../", 3) == 0)
	{
		if (access(cmd[0], X_OK) == 0)
			return (ft_strdup(cmd[0]));
	}
	env_value = get_env_value(shell->env, "PATH");
	if (!env_value)
		return (NULL);
	split_paths = ft_split(env_value, ':');
	if (!split_paths)
		return (perror("malloc failed"), NULL);
	if (split_paths[0] == NULL)
	{
		perror("command not found");
		shell->exit_code = 127;
		return (NULL);
	}
	path = find_exec_path(split_paths, cmd[0]);
	ft_free_split(split_paths);
	if (!path || path[0] == '\0')
	{
		if (!path)
			perror("malloc failed");
		else
			perror("command not found");
		shell->exit_code = 127;
		return (NULL);
	}
	return (path);
}

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
