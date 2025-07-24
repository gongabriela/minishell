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
	free(tree);
}
