/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:50:23 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/14 14:50:23 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_ast(t_shell *shell, t_token *tokens)
{
	t_exec	*node;

	while (tokens)
	{
		if (tokens->type == CMD)
		{
			node = create_node_cmd(shell, &tokens);
			if (!node)
				return (0); //melhorar handling error
		}
		add_node_to_tree(&shell->tree, node);
	}
	return (1);
}

t_exec	*create_node_cmd(t_shell *shell, t_token **tokens)
{
	t_exec	*node;

	node = malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
	node->cmd = get_cmd_and_args(tokens, shell);
	if (!node->cmd)
		return (NULL);
	node->type = CMD;
	node->next = NULL;
	return (node);
}

//ta simples como uma LL, tem q adicionar o left/right
void	add_node_to_tree(t_exec **tree, t_exec *node)
{
	t_exec	*current;

	if (!*tree)
		*tree = node;
	else
	{
		current = *tree;
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

//melhorar essa funcao para quando tiver mais de um comando
char	**get_cmd_and_args(t_token **tokens, t_shell *shell)
{
	char	**cmd;
	int		i;

	i = 0;
	while (*tokens && (*tokens)->type == CMD)
	{
		i++;
		*tokens = (*tokens)->next;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	*tokens = shell->tokens; //basicamente aqui, nao vai funcionar se tiver mais de um comando
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
