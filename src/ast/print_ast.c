/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:14:38 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/17 18:14:38 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_ast(t_exec *node, int level)
{
    int i;

    if (!node)
        return;
    for (i = 0; i < level; i++)
        printf("  "); // Indentação para visualizar a hierarquia
    if (node->type == CMD)
    {
        printf("CMD: ");
        for (int j = 0; node->cmd && node->cmd[j]; j++)
            printf("%s ", node->cmd[j]);
        printf("\n");
    }
    else if (node->type == FILENAME)
    {
        printf("FILENAME: %s\n", node->filename);
    }
    else if (node->type == DELIMITER)
    {
        printf("DELIMITER: %s\n", node->delimiter);
    }
    else
    {
        printf("OP: %s\n", node->oprt);
    }
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}
