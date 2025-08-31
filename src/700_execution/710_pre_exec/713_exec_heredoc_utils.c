/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:06:35 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/11 15:06:35 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Child process logic for handling heredoc input and file writing.
 *
 * Opens the heredoc file, writes user input, and exits the process.
 * @param tree Pointer to the AST node.
 * @param shell Pointer to the shell state structure.
 * @param heredoc Pointer to the heredoc structure.
 */
void	heredoc_child_process(t_exec *tree, t_shell *shell, t_hdc *heredoc)
{
	heredoc_signal_setup(shell);
	heredoc->fd = open(heredoc->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (heredoc->fd < 0)
	{
		perror("open failed");
		ft_exit(shell, -1);
	}
	get_heredoc_input(tree, heredoc, shell);
	close(heredoc->fd);
	free_exit_child(shell, 0);
}

/**
 * @brief Allocates and returns a unique heredoc filename string.
 *
 * Combines a temporary string and an index to create a unique filename.
 * @param shell Pointer to the shell state structure.
 * @param temp Temporary string to use as a base for the filename.
 * @param i Index to ensure uniqueness.
 * @return Pointer to the allocated filename string.
 */
char	*heredoc_alloc_name(t_shell *shell, char *temp, int i)
{
	char	*i_str;
	char	*file_name;

	i_str = ft_itoa(i);
	file_name = ft_strjoin(temp, i_str);
	if (!file_name)
	{
		perror("malloc failed");
		free(i_str);
		free(temp);
		ft_exit(shell, -1);
	}
	free(i_str);
	free(temp);
	return (file_name);
}

/**
 * @brief Generates a unique filename for a heredoc temporary file.
 *
 * Uses the process ID and a static counter to ensure uniqueness.
 * @param shell Pointer to the shell state structure.
 * @return Pointer to the allocated filename string.
 */
char	*get_random_name(t_shell *shell)
{
	static int	i = 0;
	char		*pid;
	char		*temp;
	char		*file_name;

	pid = ft_itoa(getpid());
	temp = ft_strjoin("/tmp/.heredoc_", pid);
	if (!temp)
	{
		perror("malloc failed");
		free(pid);
		ft_exit(shell, -1);
	}
	file_name = heredoc_alloc_name(shell, temp, i++);
	free(pid);
	return (file_name);
}

/**
 * @brief Frees the heredoc structure and deletes the associated temporary file.
 *
 * Unlinks and frees the heredoc filename, then frees the structure itself.
 * @param heredoc Pointer to the heredoc structure to free.
 */
/* void	free_heredoc_struct(t_hdc *heredoc)
{
	if (heredoc->file_name)
	{
		unlink(heredoc->file_name);
		free(heredoc->file_name);
	}
	free(heredoc);
} */
