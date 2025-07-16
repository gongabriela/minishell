/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:04:39 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/09 10:04:39 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execution(t_exec *tree, t_shell *shell)
{
	if (tree->type == CMD)
	{
		if (is_builtin(tree->cmd))
			execute_builtin(shell, tree, tree->cmd);
		else
			execute_external_cmd(tree, shell);
	}
}

int	is_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_shell *shell, t_exec *tree, char **cmd)
{
	(void)tree;
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		echo(shell, cmd);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		env(shell);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		pwd(shell);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		ft_exit_builtin(shell, cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		cd(shell, cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		export(shell, cmd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		unset(shell, cmd);
}

void	execute_external_cmd(t_exec *tree, t_shell *shell)
{
	pid_t	pid;
	char	*path;

	path = get_cmd_path(tree->cmd, shell);
	if (!path)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
		shell->exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		if (execve(path, tree->cmd, shell->envp) == -1)
		{
			perror("Execution failed");
			free(path);
			ft_exit(shell, 1);
		}
	}
	waitpid(pid, &shell->exit_code, 0);
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
