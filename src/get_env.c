/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:44:28 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/03 11:44:28 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Creates a new environment variable node from a string.
 *
 * Allocates and initializes a t_env node from a "KEY=VALUE" string.
 * If allocation fails, calls ft_error and exits.
 *
 * @param env The environment string ("KEY=VALUE").
 * @param shell Pointer to the shell structure for error handling.
 * @return Pointer to the newly created t_env node.
 */
t_env	*create_env_node(char *env, t_shell *shell)
{
	t_env	*node;
	int		j;

	node = malloc(sizeof(t_env));
	if (!node)
		return (perror("malloc failed"), ft_exit(shell, -1), NULL);
	ft_memset(node, 0, sizeof(t_env));
	j = 0;
	while (env[j] && env[j] != '=')
		j++;
	node->key = ft_substr(env, 0, j);
	if (!node->key)
		return (perror("malloc failed"), ft_exit(shell, -1), NULL);
	if (env[j] == '=')
	{
		node->content = ft_substr(env, j + 1, ft_strlen(env) - j - 1);
		if (!node->content)
			return (perror("malloc failed"), ft_exit(shell, -1), NULL);
	}
	else
		node->content = NULL;
	node->export = true;
	node->env = true;
	return (node);
}

/**
 * @brief Initializes the shell environment linked list from envp.
 *
 * Parses envp and creates a linked list of t_env nodes.
 * Updates shell->cmd_paths if "PATH" is found.
 *
 * @param shell Pointer to the shell structure.
 * @param envp Null-terminated array of environment strings.
 */
void	get_env(t_shell *shell, char **envp)
{
	t_env	*node;
	int		i;

	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i], shell);
		ft_lstadd_back_env(&shell->env, node);
		i++;
	}
	shell->pwd = getcwd(NULL, 0);
	if (!shell->pwd)
		return (perror("pwd"), ft_exit(shell, -1));
}

/**
 * @brief Adds a new node to the end of the environment list.
 *
 * Appends the given t_env node to the end of the linked list.
 *
 * @param lst Pointer to the head of the environment list.
 * @param new The new node to add.
 */
void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
