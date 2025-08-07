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
	int	*pipe_index;
	int	i;

	execute_heredocs(tree, shell);
	if (shell->cmd_total > 1)
	{
		shell->pipe_fds = init_pipes(shell);
		create_pipes(shell, tree, shell->pipe_fds, shell->cmd_total - 2);
	}
	i = shell->cmd_total - 2;
	pipe_index = &i;
	execute_redirs(tree, shell->pipe_fds, pipe_index);
	shell->pids = malloc(sizeof(pid_t) * shell->cmd_total);
	if (!shell->pids)
		perror("malloc failed");
}

void	execute_redirs(t_exec *tree, int **pipe_fds, int *i)
{
	if (!tree)
		return ;
	if (tree->type == REDIR_IN)
		handle_infile(tree, tree->right->filename);
	else if (tree->type == REDIR_OUT)
		handle_outfile(tree, tree->right->filename);
	else if (tree->type == APPEND)
		handle_append(tree, tree->right->filename);
	else if (tree->type == HEREDOC)
		handle_heredoc(tree);
	else if (tree->type == PIPE)
		handle_pipe(tree, pipe_fds, i);
	execute_redirs(tree->left, pipe_fds, i);
	execute_redirs(tree->right, pipe_fds, i);
}

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

void	exec_cmd(t_exec *tree, t_shell *shell, int index)
{
	pid_t	pid;
	char	*path;

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
	{
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

