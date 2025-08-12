/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   830_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:48:51 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/12 12:25:51 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Implements the env builtin command.
 *
 * Prints env vars to stdout and sets the shell->exit_code to 0.
 * @param shell Pointer to the shell state structure.
 */
void	env(t_shell *shell)
{
	print_env_list(shell->env);
	shell->exit_code = 0;
}

/**
 * @brief Prints all environment variables in the environment list.
 *
 * Iterates through the linked list and prints vars marked as env variables.
 * @param env Pointer to the head of the environment variable list.
 */
void	print_env_list(t_env *env)
{
	while (env)
	{
		if (env->env == true)
			printf("%s=%s\n", env->key, env->content);
		env = env->next;
	}
}
