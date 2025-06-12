/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:44:55 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/03 11:44:55 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * Iterates through the array, freeing each string, then frees the array itself.
 *
 * @param cmd The NULL-terminated array of strings to free.
 */
void	free_cmd_paths(char **cmd)
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

/**
 * @brief Frees a linked list of t_env environment variable nodes.
 *
 * Iterates through the list, freeing the key, content, and node itself.
 *
 * @param env Pointer to the head of the t_env linked list.
 */
void	free_struct_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->content);
		free(env);
		env = tmp;
	}
}

/**
 * @brief Frees all dynamically allocated memory in the t_shell struct.
 *
 * Frees the prompt, input, environment list, and command paths.
 * Re-initializes the shell struct after freeing.
 *
 * @param shell Pointer to the t_shell struct to free.
 */
void	ft_free_shell(t_shell *shell)
{
	if (shell->prompt != NULL)
		free(shell->prompt);
	if (shell->input != NULL)
		free(shell->input);
	free_struct_env(shell->env);
	free_cmd_paths(shell->cmd_paths);
	init_structs(shell);
}

/**
 * @brief Frees all resources and exits the shell.
 *
 * Calls ft_free_shell to free dynamically allocated memory in the t_shell struct,
 * clears the readline history, and exits the program with the given exit code.
 *
 * @param shell Pointer to the t_shell struct to free.
 * @param exit_code The exit status code to return to the operating system.
 */
void	ft_exit(t_shell *shell, int exit_code)
{
	ft_free_shell(shell);
	rl_clear_history();
	exit(exit_code);
}
