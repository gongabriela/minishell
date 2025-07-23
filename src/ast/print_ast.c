/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:49:42 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/17 17:49:42 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_ast(t_exec *node, int level)
{
	int	i;

	if (!node)
		return ;

	// Indentação para mostrar o nível hierárquico do nó
	for (i = 0; i < level; i++)
		printf("  ");

	// Exibe tipo do nó
	if (node->type == CMD)
	{
		printf("CMD Node\n");

		for (i = 0; node->cmd && node->cmd[i]; i++)
		{
			for (int j = 0; j < level + 1; j++)
				printf("  ");
			printf("arg[%d]: %s\n", i, node->cmd[i]);
		}
	}
	else
	{
		printf("OP Node: %s\n", node->oprt);
	}

	// Indenta e mostra stdin e stdout
	for (i = 0; i < level + 1; i++)
		printf("  ");
	//printf("stdin: %d, stdout: %d\n", node->stdin, node->stdout);

	// Recursão para esquerda e direita
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

