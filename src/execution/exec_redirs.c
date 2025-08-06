/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:17:45 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/24 14:17:45 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_redirs(t_exec *tree, int **pipe_fds, int *i)
{
	if (!tree)
		return ;
	if (tree->type == REDIR_IN)
		handle_infile(tree, tree->right->filename);
	else if (tree->type == REDIR_OUT)
		handle_outfile(tree, tree->right->filename);
	else if (tree->type == APPEND)
		handle_append(tree, tree->right->filename);
	else if(tree->type == HEREDOC)
		handle_heredoc(tree);
	else if (tree->type == PIPE)
		handle_pipe(tree, pipe_fds, i);
	execute_redirs(tree->left, pipe_fds, i);
	execute_redirs(tree->right, pipe_fds, i);
}

void	handle_heredoc(t_exec *tree)
{
	tree->heredoc->fd = open(tree->heredoc->file_name, O_RDONLY);
	if (tree->heredoc->fd < 0)
	{
		perror("open failed");
		return; //melhorar esse handle error aqui
	}
	if (tree->left)
		tree->left->stdin = tree->heredoc->fd;
	if (tree->stdout != STDOUT_FILENO)
		tree->left->stdout = tree->stdout;
}

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