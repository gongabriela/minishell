/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:34:31 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/20 13:34:31 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pre_execution(t_exec *tree, t_shell *shell)
{
	if (shell->cmd_total > 1)
	{
		shell->pipe_fds = init_pipes(shell);
		create_pipes(shell, tree, shell->pipe_fds, shell->cmd_total - 2);
		get_redir_info_pipes(shell, tree, shell->pipe_fds, shell->cmd_total - 2);
	}
	shell->pids = malloc(sizeof(pid_t) * shell->cmd_total);
	if (!shell->pids)
		perror("malloc failed");
}

void	execution(t_exec *tree, t_shell *shell, int *pid_index)
{
	if (tree->type == PIPE)
	{
		if (tree->left)
			execution(tree->left, shell, pid_index);
		if (tree->right)
			execution(tree->right, shell, pid_index);
	}
	if (tree->type == CMD)
	{
		exec_cmd(tree, shell, *pid_index);
		(*pid_index)++;
	}
}


void	exec_cmd(t_exec *tree, t_shell *shell, int index)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
	{
		redir_io(tree, shell);
		if (is_builtin(tree->cmd))
		{
			execute_builtin(shell, tree, tree->cmd);
			exit(shell->exit_code);
		}
		else
		{
			path = get_cmd_path(tree->cmd, shell);
			if (!path)
			{
				perror("command not found");
				exit(127);
			}
			execve(path, tree->cmd, shell->envp);
			perror("exceve failed");
			exit(127);
		}
	}
	else
		shell->pids[index] = pid;
}

void	redir_io(t_exec *tree, t_shell *shell)
{
	int	i;

	if (tree->stdin != STDIN_FILENO)
	{
		dup2(tree->stdin, STDIN_FILENO);
		close(tree->stdin);
	}
	if (tree->stdout != STDOUT_FILENO)
	{
		dup2(tree->stdout, STDOUT_FILENO);
		close(tree->stdout);
	}
	if (shell->pipe_fds)
	{
		i = 0;
		while (i < shell->cmd_total - 1)
		{
			if (shell->pipe_fds[i][0] != tree->stdin &&
				shell->pipe_fds[i][0] != tree->stdout)
				close(shell->pipe_fds[i][0]);
			if (shell->pipe_fds[i][1] != tree->stdin &&
				shell->pipe_fds[i][1] != tree->stdout)
				close(shell->pipe_fds[i][1]);
			i++;
		}
	}
}
//-----------------------------------PATH---------------------------------//
char	*get_cmd_path(char **cmd, t_shell *shell)
{
	char	**split_paths;
	char	*env_value;
	char	*path;

	if (cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2) == 0 || ft_strncmp(cmd[0], "../", 3) == 0)
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