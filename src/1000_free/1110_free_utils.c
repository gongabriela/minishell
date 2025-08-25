/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1110_free_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:34:52 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/25 16:34:52 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_exit_child(t_shell *shell, int exit_code)
{
	close_all_fds(shell->tree);
	close_all_pipes(shell);
	ft_free_shell(shell);
	free_struct_env(shell->env);
	if (shell->pwd != NULL)
		free(shell->pwd);
	exit(exit_code);
}

void	unlink_heredocs(t_exec *tree)
{
	if (!tree)
		return ;
	if (tree->type == HEREDOC)
	{
		if (tree->heredoc && tree->heredoc->file_name)
			unlink(tree->heredoc->file_name);
	}
	unlink_heredocs(tree->left);
	unlink_heredocs(tree->right);
}
