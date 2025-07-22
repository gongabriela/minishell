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
	}
}

void	execution(t_exec *tree, t_shell *shell)
{
	if (!tree)
		return ;
	if (tree->type == PIPE)
	{
		execution(tree->left, shell);
		execution(tree->right, shell);
	}
	if (tree->type == CMD)
	{
		if (is_builtin(tree->cmd))
			execute_builtin(shell, tree, tree->cmd);
		else
			execute_external_cmd(tree, shell, shell->pid_index++);
	}
}
