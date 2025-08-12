/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   852_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:53:10 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/12 11:47:59 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Creates a deep copy of an environment variable node.
 *
 * @param src The source environment variable node.
 * @return Pointer to the new copied node, or NULL on allocation failure.
 */
t_env	*copy_env_node(t_env *src)
{
	t_env	*copy;

	copy = malloc(sizeof(t_env));
	if (!copy)
		return (NULL);
	copy->key = ft_strdup(src->key);
	if (src->content)
		copy->content = ft_strdup(src->content);
	else
		copy->content = NULL;
	copy->export = src->export;
	copy->next = NULL;
	return (copy);
}

/**
 * @brief Inserts a node into a sorted linked list of environment variables.
 *
 * @param sorted Pointer to the head of the sorted list.
 * @param node The node to insert.
 */
void	insert_sorted(t_env **sorted, t_env *node)
{
	t_env	*curr;
	t_env	*prev;

	curr = *sorted;
	prev = NULL;
	while (curr && ft_strncmp(node->key, curr->key, ft_strlen(node->key) + 1)
		> 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
	{
		node->next = *sorted;
		*sorted = node;
	}
	else
	{
		prev->next = node;
		node->next = curr;
	}
}

/**
 * @brief Prints the sorted environment variables in export format.
 *
 * @param sorted The head of the sorted environment variable list.
 */
void	print_sorted_env(t_env *sorted)
{
	while (sorted)
	{
		printf("declare -x %s", sorted->key);
		if (sorted->content)
			printf("=\"%s\"", sorted->content);
		printf("\n");
		sorted = sorted->next;
	}
}

/**
 * @brief Frees a linked list of environment variable nodes.
 *
 * @param lst The head of the list to free.
 */
void	free_env_list(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->key);
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = tmp;
	}
}

/**
 * @brief Prints the export table in sorted order.
 *
 * @param shell The shell state containing the environment list.
 */
void	print_export_table(t_shell *shell)
{
	t_env	*curr;
	t_env	*sorted;
	t_env	*copy;

	curr = shell->env;
	sorted = NULL;
	while (curr)
	{
		if (curr->export)
		{
			copy = copy_env_node(curr);
			if (copy)
				insert_sorted(&sorted, copy);
		}
		curr = curr->next;
	}
	print_sorted_env(sorted);
	free_env_list(sorted);
	shell->exit_code = 0;
}
