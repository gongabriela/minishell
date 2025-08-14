/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:28:31 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/21 11:28:31 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Prepares the shell for command execution by setting up pipes, heredocs,
 *  and redirections.
 *
 * Initializes pipes, executes heredocs, sets up redirections, and allocates
 * memory for process IDs.
 * @param tree Pointer to the root of the AST.
 * @param shell Pointer to the shell state structure.
 */
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
	if (shell->cmd_total == 1 && is_builtin(tree->cmd))
		return ;
	shell->pids = malloc(sizeof(pid_t) * shell->cmd_total);
	if (!shell->pids)
		perror("malloc failed");
	ft_memset(shell->pids, -1, sizeof(pid_t) * shell->cmd_total);
}
