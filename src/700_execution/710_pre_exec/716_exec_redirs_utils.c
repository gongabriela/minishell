/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:06:58 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/11 15:06:58 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Opens the heredoc file and sets up input/output for the left child.
 *
 * Updates the left child's stdin and stdout based on the heredoc.
 * @param tree Pointer to the AST node containing the heredoc.
 */
void	handle_heredoc(t_exec *tree)
{
	tree->heredoc->fd = open(tree->heredoc->file_name, O_RDONLY);
	if (tree->heredoc->fd < 0)
	{
		perror("open failed");
		return ;
	}
	if (tree->left)
		tree->left->stdin = tree->heredoc->fd;
	if (tree->stdout != STDOUT_FILENO)
		tree->left->stdout = tree->stdout;
}

/**
 * @brief Sets up the pipe file descriptors for the childrens of a PIPE node.
 *
 * Updates stdin/stdout for the childrens and decrements the pipe index.
 * @param tree Pointer to the PIPE node in the AST.
 * @param pipe_fds Array of pipe file descriptors.
 * @param i Pointer to the current pipe index.
 */
void	handle_pipe(t_exec *tree, int **pipe_fds, int *i)
{
	if (tree->left)
		tree->left->stdout = pipe_fds[*i][1];
	if (tree->right)
	{
		tree->right->stdin = pipe_fds[*i][0];
		if (tree->stdout != STDOUT_FILENO)
			tree->right->stdout = tree->stdout;
	}
	(*i)--;
}

/**
 * @brief Handles input redirection for a command node.
 *
 * Opens the input file and sets the left child's stdin.
 * @param tree Pointer to the AST node.
 * @param file Name of the input file.
 */
void	handle_infile(t_exec *tree, char *file)
{
	int	fd;

	if (tree->stdin != STDIN_FILENO)
	{
		tree->left->stdin = tree->stdin;
		return ;
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			printf("-bash: %s: No such file or directory\n", file);
		else if (errno == EACCES)
			printf("-bash: %s: Permission denied\n", file);
		else
			perror("open failed");
	}
	else
		tree->left->stdin = fd;
	if (tree->stdout != 1)
		tree->left->stdout = tree->stdout;
}

/**
 * @brief Handles output redirection for a command node.
 *
 * Opens the output file and sets the left child's stdout.
 * @param tree Pointer to the AST node.
 * @param file Name of the output file.
 */
void	handle_outfile(t_exec *tree, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			printf("-bash: %s: Permission denied\n", file);
		else
			perror("pipex");
	}
	if (tree->stdout != STDOUT_FILENO)
	{
		tree->left->stdout = tree->stdout;
		close(fd);
	}
	else
		tree->left->stdout = fd;
	if (tree->stdin != 0)
		tree->left->stdin = tree->stdin;
}

/**
 * @brief Handles append redirection for a command node.
 *
 * Opens the file in append mode and sets the left child's stdout.
 * @param tree Pointer to the AST node.
 * @param file Name of the file to append to.
 */
void	handle_append(t_exec *tree, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			printf("-bash: %s: Permission denied\n", file);
		else
			perror("pipex");
	}
	else
		tree->left->stdout = fd;
}
