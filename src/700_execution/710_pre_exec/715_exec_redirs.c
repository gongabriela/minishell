/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:17:45 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/24 14:17:45 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Recursively sets up input/output redirections and pipes in the AST.
 *
 * Handles all redirection and pipe nodes, updating file descriptors as needed.
 * @param tree Pointer to the root of the AST.
 * @param pipe_fds Array of pipe file descriptors.
 * @param i Pointer to the current pipe index.
 */
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

