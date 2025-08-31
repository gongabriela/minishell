/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   717_exec_redirs_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:23:56 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/25 16:23:56 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	handle_infile_redir(t_exec *tree, int fd)
{
	tree->left->stdin = tree->stdin;
	if (tree->in_file == true)
		tree->left->in_file = true;
	if (fd > 0)
		close(fd);
}

void	handle_outfile_redir(t_exec *tree, int fd)
{
	if (tree->left && tree->stdout != STDOUT_FILENO)
	{
		tree->left->stdout = tree->stdout;
		if (tree->out_file == true)
			tree->left->out_file = true;
		if (fd > 0)
			close(fd);
	}
	else
	{
		if (tree->left)
		{
			close_opened_fds(tree->left, 1);
			tree->left->stdout = fd;
			tree->left->out_file = true;
		}
	}
}

void	error_msg_redir(t_exec *tree, int err_code, char *file, int std)
{
	if (err_code == ENOENT)
		printf("-bash: %s: No such file or directory\n", file);
	else if (err_code == EACCES)
		printf("-bash: %s: Permission denied\n", file);
	else if (err_code == EISDIR)
		printf("-bash: %s: Is a directory\n", file);
	else if (std == 2)
		printf("-bash: heredoc failed\n");
	else
		perror("open failed: Error creating/opening file");
	if (std == 2)
	{
		tree->heredoc->fd = -1;
		free_heredoc_struct(tree->heredoc);
	}
	if (!tree->left)
		return ;
	close_opened_fds(tree, std);
	if (std == 0 || std == 2)
		tree->left->stdin = -1;
	if (std == 1)
		tree->left->stdout = -1;
}

void	close_opened_fds(t_exec *tree, int std)
{
	if (!tree)
		return ;
	if (tree->type != CMD)
		return ;
	if (std == 0 || std == 2)
	{
		if (tree->stdin > 0 && tree->in_file == true)
			close(tree->stdin);
	}
	else if (std == 1)
	{
		if (tree->stdout > 1 && tree->out_file == true)
			close(tree->stdout);
	}
}

void	close_all_fds(t_exec *tree)
{
	if (!tree)
		return ;
	if (tree->stdin > 0 && tree->in_file == true)
		close(tree->stdin);
	if (tree->stdout > 1 && tree->out_file == true)
		close(tree->stdout);
	close_all_fds(tree->left);
	close_all_fds(tree->right);
}
