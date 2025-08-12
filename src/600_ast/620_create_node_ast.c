/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:49:26 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/24 13:49:26 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Creates a new AST node based on the curr token & updates token pointer.
 *
 * Allocates and initializes a t_exec node, determines its type,
 * and fills its fields accordingly.
 * Handles errors and syntax validation for pipes and redirections.
 * @param tokens Pointer to the token list pointer.
 * @param shell Pointer to the shell state structure.
 * @return Pointer to the created node, or NULL on failure.
 */
t_exec	*create_node_ast(t_token **tokens, t_shell *shell)
{
	int		code;
	t_exec	*node;

	node = malloc(sizeof(t_exec));
	if (!node)
		return (perror("malloc failed"), ft_exit(shell, 1), NULL);
	init_node(node, tokens);
	code = 0;
	if (node->type == PIPE)
		code = create_node_pipe(node, tokens, shell);
	else if (node->type == REDIR_IN || node->type == REDIR_OUT
		|| node->type == APPEND || node->type == HEREDOC)
		code = create_node_redir(node, tokens, shell);
	else if (node->type == CMD)
		code = create_node_cmd(node, tokens, shell);
	if (*tokens && node->type != CMD)
		*tokens = (*tokens)->next;
	if (code != 0)
	{
		shell->exit_code = 2;
		return (ft_free_node(node), NULL);
	}
	return (node);
}

/**
 * @brief Init a t_exec node with default values and sets its type/content.
 *
 * Sets all pointers to NULL, file descriptors to STDIN/STDOUT,
 * and copies content for filename/delimiter types.
 * @param node Pointer to the node to initialize.
 * @param tokens Pointer to the token list pointer.
 */
void	init_node(t_exec *node, t_token **tokens)
{
	node->cmd = NULL;
	node->oprt = NULL;
	node->filename = NULL;
	node->delimiter = NULL;
	node->left = NULL;
	node->right = NULL;
	node->stdin = STDIN_FILENO;
	node->stdout = STDOUT_FILENO;
	node->type = (*tokens)->type;
	node->heredoc = NULL;
	if (node->type == FILENAME)
		node->filename = ft_strdup((*tokens)->content);
	else if (node->type == DELIMITER)
		node->delimiter = ft_strdup((*tokens)->content);
}

/**
 * @brief Initializes a pipe node and checks for syntax errors.
 *
 * Duplicates the pipe operator string and validates the next token.
 * @param node Pointer to the node to initialize.
 * @param tokens Pointer to the token list pointer.
 * @param shell Pointer to the shell state structure.
 * @return 0 on success, -1 on syntax error or allocation failure.
 */
int	create_node_pipe(t_exec *node, t_token **tokens, t_shell *shell)
{
	node->oprt = ft_strdup((*tokens)->content);
	if (!node->oprt)
		return (free(node), perror("malloc failed"), ft_exit(shell, 1), -1);
	if (!(*tokens)->next || (*tokens)->next->type == PIPE)
	{
		printf("-bash: syntax error near unexpected token `|'\n");
		return (-1);
	}
	return (0);
}

/**
 * @brief Initializes a redirection node and checks for syntax errors.
 *
 * Duplicates the redir operator str and validates the next token,
 * updating its type if needed.
 * @param node Pointer to the node to initialize.
 * @param tokens Pointer to the token list pointer.
 * @param shell Pointer to the shell state structure.
 * @return 0 on success, -1 on syntax error or allocation failure.
 */
int	create_node_redir(t_exec *node, t_token **tokens, t_shell *shell)
{
	node->oprt = ft_strdup((*tokens)->content);
	if (!node->oprt)
		return (free(node), perror("malloc failed"), ft_exit(shell, 1), -1);
	if ((*tokens)->next)
	{
		if ((*tokens)->next->type == CMD)
		{
			if (node->type == HEREDOC)
				(*tokens)->next->type = DELIMITER;
			else
				(*tokens)->next->type = FILENAME;
		}
		else
			return (printf("-bash: syntax error near unexpected token `%s'\n",
					(*tokens)->next->content), -1);
	}
	else
		return (printf("-bash: syntax error near unexpected token `newline'\n"),
			-1);
	return (0);
}

/**
 * @brief Init a command node by extracting command and arguments from tokens.
 *
 * Allocates and fills the cmd array for the node.
 * @param node Pointer to the node to initialize.
 * @param tokens Pointer to the token list pointer.
 * @param shell Pointer to the shell state structure.
 * @return 0 on success, -1 on allocation failure.
 */
int	create_node_cmd(t_exec *node, t_token **tokens, t_shell *shell)
{
	if ((*tokens)->next && (*tokens)->next->type == CMD)
		node->cmd = get_full_cmd(tokens);
	else
		node->cmd = get_simple_cmd(tokens);
	if (!node->cmd)
		return (free(node), perror("malloc failed"), ft_exit(shell, 1), -1);
	return (0);
}
