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

#include "../../inc/minishell.h"

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
	if (shell->tokens != NULL)
		free_struct_tokens(shell->tokens);
	if (shell->tree != NULL)
		ft_free_ast(shell->tree);
	if (shell->pids != NULL)
		free(shell->pids);
	/*if (shell->envp != NULL)
		free_envp_array(shell->envp);*/
	init_structs(shell);
}

/**
 * @brief Frees all resources and exits the shell.
 *
 * Calls ft_free_shell to free dynamically allocated memory in the
 * t_shell struct,
 * clears the readline history, and exits the program with the given exit code.
 *
 * @param shell Pointer to the t_shell struct to free.
 * @param exit_code The exit status code to return to the operating system.
 */
void	ft_exit(t_shell *shell, int exit_code)
{
	ft_free_shell(shell);
	if (shell->pwd != NULL)
		free(shell->pwd);
	free_struct_env(shell->env);
	rl_clear_history();
	exit(exit_code);
}

void	free_struct_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->content)
			free(tokens->content);
		free(tokens);
		tokens = tmp;
	}
}

/**
 * @brief Frees the heredoc structure and deletes the associated temporary file.
 *
 * Unlinks and frees the heredoc filename, then frees the structure itself.
 * @param heredoc Pointer to the heredoc structure to free.
 */
void	free_heredoc_struct(t_hdc *heredoc)
{
	if (heredoc->file_name)
	{
		unlink(heredoc->file_name);
		free(heredoc->file_name);
		//if (heredoc->fd != -1)
			//close(heredoc->fd);
	}
	free(heredoc);
}

void	free_exit_child(t_shell *shell, int exit_code)
{
	ft_free_shell(shell);
	free_struct_env(shell->env);
	if (shell->pwd != NULL)
		free(shell->pwd);
	exit(exit_code);
}