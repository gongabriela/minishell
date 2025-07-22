/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:04:46 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/17 15:04:46 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_ast(t_shell *shell, t_token *tokens)
{
	t_exec	*node;
	t_exec	*root;

	root = NULL;
	while (tokens)
	{
		node = create_node_ast(&tokens);
		if (!node)
			ft_exit(shell, 1);
		if (!root)
			root = node;
		else
			add_node_ast(node, &root);
	}
	shell->tree = root;
}

t_exec	*create_node_ast(t_token **tokens)
{
	t_exec *node;

	node = malloc(sizeof(t_exec));
	if (!node)
		return (perror("malloc failed"), NULL);
	node->cmd = NULL;
	node->oprt = NULL;
	node->left = NULL;
	node->right = NULL;
	node->stdin = 0;
	node->stdout = 1;
	node->type = (*tokens)->type;
	if (node->type == CMD)
	{
		if ((*tokens)->next && (*tokens)->next->type == CMD)
			node->cmd = get_full_cmd(tokens);
		else
			node->cmd = get_simple_cmd(tokens);
		if (!node->cmd)
			return (free(node), perror("malloc failed"), NULL);
	}
	else
	{
		node->oprt = ft_strdup((*tokens)->content);
		if (!node->oprt)
			return (free(node), perror("malloc failed"), NULL);
		if (*tokens)
			*tokens = (*tokens)->next;
	}
	return (node);
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

void	add_node_ast(t_exec *node, t_exec **root)
{
	if (node->type == CMD)
	{
		if (!(*root)->left)
			(*root)->left = node;
		else if (!(*root)->right)
			(*root)->right = node;
	}
	else
	{
		node->left = *root;
		*root = node;
	}
}

void	ft_free_ast(t_exec *tree)
{
	if (!tree)
		return;
	ft_free_ast(tree->left);
	ft_free_ast(tree->right);
	if (tree->cmd)
		free_cmd_and_args(tree->cmd);
	if (tree->oprt)
		free(tree->oprt);
	free(tree);
}

char	**get_full_cmd(t_token **tokens)
{
	t_token *temp;
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
		{
			free_cmd_and_args(cmd);
			return (NULL);
		}
		i++;
		*tokens = (*tokens)->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

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
