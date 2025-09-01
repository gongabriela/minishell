/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:14:33 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/17 18:14:33 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Creates the AST for the shell commands.
 *
 * Iterates through the token list, creates AST nodes, building the tree struct.
 * Sets the root of the tree in the shell structure.
 * @param shell Pointer to the shell state structure.
 * @param tokens Pointer to the head of the token list.
 * @return 1 on success, 0 on failure.
 */
int	create_ast(t_shell *shell, t_token *tokens)
{
	t_exec	*node;
	t_exec	*root;

	root = NULL;
	if (!tokens)
		return (0);
	while (tokens)
	{
		node = create_node_ast(&tokens, shell);
		if (!node)
			return (ft_free_ast(root), 0);
		if (!root)
			root = node;
		else
			add_node_ast(node, &root);
	}
	shell->tree = root;
	return (1);
}

/**
 * @brief Adds a node to the AST according to its type.
 *
 * Handles command, filename, delimiter, and operator nodes.
 * @param node The node to add.
 * @param root Pointer to the root of the AST.
 */
void	add_node_ast(t_exec *node, t_exec **root)
{
	if (node->type == CMD)
	{
		if (!(*root)->left)
			(*root)->left = node;
		else if (!(*root)->right)
			(*root)->right = node;
		else
			ft_free_node(node);
	}
	else if (node->type == FILENAME || node->type == DELIMITER)
		(*root)->right = node;
	else
	{
		node->left = *root;
		*root = node;
	}
}

/**
 * @brief Extracts a simple command (single token) from the token list.
 *
 * Allocates and returns a NULL-terminated array with one command string.
 * Advances the token pointer.
 * @param tokens Pointer to the token list pointer.
 * @return Array of command strings, or NULL on failure.
 */
char	**get_simple_cmd(t_token **tokens)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 2);
	if (!cmd)
		return (NULL);
	cmd[0] = ft_strdup((*tokens)->content);
	if (!cmd[0])
		perror("malloc failed");
	cmd[1] = NULL;
	*tokens = (*tokens)->next;
	return (cmd);
}

/**
 * @brief Extracts a full command (multiple tokens) from the token list.
 *
 * Allocates and returns a NULL-terminated array of command and argument strings.
 * Advances the token pointer past all command tokens.
 * @param tokens Pointer to the token list pointer.
 * @return Array of command/argument strings, or NULL on failure.
 */
char	**get_full_cmd(t_token **tokens)
{
	t_token	*temp;
	char	**cmd;
	int		i;

	i = 0;
	temp = *tokens;
	while (temp && temp->type == CMD)
	{
		i++;
		temp = temp->next;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type == CMD)
	{
		cmd[i] = ft_strdup((*tokens)->content);
		if (!cmd[i])
			return (free_cmd_and_args(cmd), NULL);
		i++;
		*tokens = (*tokens)->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
