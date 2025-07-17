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

#include "../../inc/minishell.h"

void	execution(t_exec *tree, t_shell *shell)
{
	/*if (tree->type == HEREDOC)
		execute_heredoc(tree, shell);
	else */if (tree->type == CMD)
	{
		if (is_builtin(tree->cmd))
			execute_builtin(shell, tree, tree->cmd);
		else
			execute_external_cmd(tree, shell);
	}
}

