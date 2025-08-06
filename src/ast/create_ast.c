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

int	create_ast(t_shell *shell, t_token *tokens)
{
	t_exec	*node;
	t_exec	*root;

	root = NULL;
	while (tokens)
	{
		node = create_node_ast(&tokens, shell);
		if (!node)
			return (0);
		if (!root)
			root = node;
		else
			add_node_ast(node, &root);
	}
	shell->tree = root;
	return (1);
}

void	add_node_ast(t_exec *node, t_exec **root)
{
	if (node->type == CMD)
	{
		if (!(*root)->left)
			(*root)->left = node;
		else if (!(*root)->right)
			(*root)->right = node;
	}
	else if (node->type == FILENAME || node->type == DELIMITER)
		(*root)->right = node;
	else
	{
		node->left = *root;
		*root = node;
	}
}

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
