/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:15:04 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/17 13:15:04 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Deletes a node from the environment variable linked list.
 *
 * Searches for the target node in the shell's env list and removes it.
 * @param shell Pointer to the shell state structure.
 * @param target Pointer to the environment node to delete.
 */
void	delete_env_node(t_shell *shell, t_env *target)
{
	t_env	*curr;
	t_env	*prev;

	if (!shell || !shell->env || !target)
		return ;
	curr = shell->env;
	prev = NULL;
	while (curr)
	{
		if (curr == target)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env = curr->next;
			free(curr->key);
			free(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

/**
 * @brief Removes a single environment variable by key.
 *
 * Searches for the env var matching the given key and deletes it.
 * @param shell Pointer to the shell state structure.
 * @param arg The key of the environment variable to remove.
 */
static void	unset_one(t_shell *shell, char *arg)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, arg, ft_strlen(env->key) + 1) == 0)
		{
			delete_env_node(shell, env);
			break ;
		}
		env = env->next;
	}
}

/**
 * @brief Implements the unset builtin command.
 *
 * Removes one or more env vars specified in args from the shell's env list.
 * Handles invalid options and sets the shell's exit code accordingly.
 * @param shell Pointer to the shell state structure.
 * @param args Array of argument strings.
 */
void	unset(t_shell *shell, char **args)
{
	int		i;
	char	temp[2];

	if (!args[1])
		return ((void)(shell->exit_code = 0));
	i = check_invalid_option(args);
	if (i > 0)
	{
		temp[0] = '-';
		temp[1] = args[1][i];
		printf("-bash: unset: %s: invalid option\n", temp);
		shell->exit_code = 2;
		return ;
	}
	while (args[i])
	{
		unset_one(shell, args[i]);
		i++;
	}
	shell->exit_code = 0;
}

int	check_invalid_option(char **args)
{
	int	i;

	i = 1;
	if (args[1][0] == '-')
	{
		while (args[1][i])
		{
			if (args[1][i] != 'n')
				return (i);
			i++;
		}
	}
	return (0);
}
