/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:26:25 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/16 17:26:25 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_external_cmd(t_exec *tree, t_shell *shell, int pid_index)
{
	char	*path;

	path = get_cmd_path(tree->cmd, shell);
	if (!path)
		return ;
	shell->pids[pid_index][0] = fork();
	if (shell->pids[pid_index][0] < 0)
	{
		perror("Fork failed");
		shell->exit_code = 1;
		return ;
	}
	if (shell->pids[pid_index][0] == 0)
	{
		if (execve(path, tree->cmd, shell->envp) == -1)
		{
			perror("Execution failed");
			free(path);
			ft_exit(shell, 1);
		}
	}
	free(path);
}

char	*get_cmd_path(char **cmd, t_shell *shell)
{
	char	**split_paths;
	char	*path;

	split_paths = ft_split(get_env_value(shell->env, "PATH"), ':');
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