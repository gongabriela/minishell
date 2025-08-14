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

void	execution(t_exec *tree, t_shell *shell, int *pid_index)
{
	if (tree->type == CMD)
	{
		exec_cmd(tree, shell, *pid_index);
		(*pid_index)++;
	}
	else
	{
		if (tree->left)
			execution(tree->left, shell, pid_index);
		if (tree->right)
			execution(tree->right, shell, pid_index);
	}
}

void	exec_cmd_child(t_exec *tree, t_shell *shell)
{
	char	*path;

	handle_signals_child();
	if (tree->stdin < 0 || tree->stdout < 0)
	{
		shell->exit_code = 1;
		exit(1);
	}
	redir_io(tree, shell);
	if (is_builtin(tree->cmd))
	{
		execute_builtin(shell, tree, tree->cmd);
		exit(shell->exit_code);
	}
	path = get_cmd_path(tree->cmd, shell);
	if (!path)
		exit(shell->exit_code);
	get_envp(shell);
	execve(path, tree->cmd, shell->envp);
	perror("exceve failed");
	exit(127);
}

void	exec_cmd(t_exec *tree, t_shell *shell, int index)
{
	pid_t	pid;

	if (shell->cmd_total == 1 && is_builtin(tree->cmd))
	{
		execute_builtin(shell, tree, tree->cmd);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
		exec_cmd_child(tree, shell);
	else
		shell->pids[index] = pid;
}

void	close_unused_pipes(t_exec *tree, t_shell *shell)
{
	int	i;

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

void	redir_io(t_exec *tree, t_shell *shell)
{
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
		close_unused_pipes(tree, shell);
}
