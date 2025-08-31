/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:04:48 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/23 17:04:48 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Frees a NULL-terminated array of command/argument strings.
 *
 * Iterates through the array, freeing each string, then frees the array itself.
 * @param cmd The array of strings to free.
 */
void	free_cmd_and_args(char **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

/**
 * @brief Frees all dynamically allocated members of a t_exec node.
 *
 * Frees all vars from the node struct.
 * @param node Pointer to the t_exec node to free.
 */
void	ft_free_node(t_exec *node)
{
	if (node->oprt)
		free(node->oprt);
	if (node->cmd)
		free_cmd_and_args(node->cmd);
	if (node->delimiter)
		free(node->delimiter);
	if (node->filename)
		free(node->filename);
	free(node);
}

/**
 * @brief Recursively frees an entire AST (Abstract Syntax Tree) of t_exec nodes.
 *
 * Traverses the tree in post-order, freeing all nodes.
 * @param tree Pointer to the root of the AST to free.
 */
void	ft_free_ast(t_exec *tree)
{
	if (!tree)
		return ;
	ft_free_ast(tree->left);
	ft_free_ast(tree->right);
	if (tree->cmd)
		free_cmd_and_args(tree->cmd);
	if (tree->oprt)
		free(tree->oprt);
	if (tree->delimiter)
		free(tree->delimiter);
	if (tree->filename)
		free(tree->filename);
	if (tree->type == HEREDOC && tree->heredoc)
		free_heredoc_struct(tree->heredoc);
	if (tree->stdin > 0)
		close(tree->stdin);
	if (tree->stdout > 1)
		close(tree->stdout);
	free(tree);
}
