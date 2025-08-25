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
	t_exec	*cmd;

	tree->heredoc->fd = open(tree->heredoc->file_name, O_RDONLY);
	cmd = tree->left;
	while (cmd && cmd->type != CMD)
		cmd = cmd->left;
	if (cmd && cmd->stdin == STDIN_FILENO)
		cmd->stdin = tree->heredoc->fd;
	if (tree->left && tree->stdout != STDOUT_FILENO)
	{
		close_opened_fds(tree->left, 2);
		tree->left->stdout = tree->stdout;
	}
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
	close_opened_fds(tree->left, 1);
	if (tree->left)
		tree->left->stdout = pipe_fds[*i][1];
	if (tree->right)
	{
		close_opened_fds(tree->right, 0);
		tree->right->stdin = pipe_fds[*i][0];
		tree->right->in_file = false;
		if (tree->stdout != STDOUT_FILENO)
		{
			close_opened_fds(tree->right, 1);
			tree->right->stdout = tree->stdout;
			tree->right->out_file = false;
		}
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

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_msg_redir(tree, errno, file, 0);
	if (!tree->left && fd > 0)
		close(fd);
	if (tree->stdin != STDIN_FILENO && tree->left)
		handle_infile_redir(tree, fd);
	else
	{
		if (tree->left)
		{
			close_opened_fds(tree->left, 0);
			tree->left->stdin = fd;
			tree->left->in_file = true;
		}
	}
	if (tree->stdout != 1 && tree->left)
	{
		close_opened_fds(tree->left, 1);
		tree->left->stdout = tree->stdout;
		tree->left->out_file = true;
	}
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
	int	if_exist;

	if_exist = (access(file, F_OK));
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_msg_redir(tree, errno, file, 1);
	if (if_exist == 0 && fd > 0)
		tree->created_out = true;
	if (!tree->left && fd > 0)
		close(fd);
	handle_outfile_redir(tree, fd);
	if (tree->stdin != 0 && tree->left)
	{
		close_opened_fds(tree->left, 0);
		tree->left->stdin = tree->stdin;
		tree->left->in_file = true;
	}
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
		error_msg_redir(tree, errno, file, 1);
	else
	{
		close_opened_fds(tree->left, 1);
		tree->left->stdout = fd;
		tree->left->out_file = true;
	}
}
