/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:05:26 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/11 15:05:26 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
/**
 * @brief Initializes the array of pipe file descriptors for command execution.
 *
 * Allocates memory for the pipes based on the total number of commands.
 * Each pipe is represented as an array of two integers.
 * @param shell Pointer to the shell state structure.
 * @return Pointer to the allocated array of pipe file descriptors,
 * or NULL on failure.
 */
int	**init_pipes(t_shell *shell)
{
	int	**pipe_fds;
	int	i;

	pipe_fds = malloc(sizeof(int *) * (shell->cmd_total - 1));
	if (!pipe_fds)
		perror("malloc failed");
	i = shell->cmd_total - 2;
	while (i >= 0)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!pipe_fds[i])
			perror("malloc failed");
		ft_memset(pipe_fds[i], 0, sizeof(int) * 2);
		i--;
	}
	return (pipe_fds);
}

/**
 * @brief Recursively creates pipes for each PIPE node in the AST.
 *
 * Traverses the AST and creates a pipe for each PIPE node,
 * storing fds in pipe_fds.
 * @param shell Pointer to the shell state structure.
 * @param tree Pointer to the root of the AST.
 * @param pipe_fds Array of pipe file descriptors.
 * @param i Current index for pipe_fds.
 * @return The next available index after creating pipes.
 */
int	create_pipes(t_shell *shell, t_exec *tree, int	**pipe_fds, int i)
{
	if (!tree)
		return (i);
	if (tree->type == PIPE)
	{
		if (pipe(pipe_fds[i]) == -1)
			perror("error creating pipe");
		i--;
	}
	i = create_pipes(shell, tree->left, pipe_fds, i);
	i = create_pipes(shell, tree->right, pipe_fds, i);
	return (i);
}

/**
 * @brief Frees the memory allocated for the array of pipe file descriptors.
 *
 * Iterates through the array and frees each pipe, then frees the array itself.
 * @param pipe_fds Array of pipe file descriptors.
 * @param cmd_total Total number of commands (used to determine array size).
 */
void	ft_free_pipes(int **pipe_fds, int cmd_total)
{
	int	i;

	if (!pipe_fds)
		return ;
	i = 0;
	while (i < cmd_total - 1)
	{
		if (pipe_fds[i])
			free(pipe_fds[i]);
		i++;
	}
	free(pipe_fds);
}
