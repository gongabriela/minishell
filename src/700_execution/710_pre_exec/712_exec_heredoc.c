/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:26:06 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/16 17:26:06 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Recursively executes heredoc for all HEREDOC nodes in the AST.
 *
 * Allocates heredoc structures and processes heredocs for each HEREDOC node.
 * @param tree Pointer to the root of the AST.
 * @param shell Pointer to the shell state structure.
 */
int	execute_heredocs(t_exec *tree, t_shell *shell)
{
	if (!tree)
		return (0);
	if (execute_heredocs(tree->left, shell) == 1)
		return (1);
	if (execute_heredocs(tree->right, shell) == 1)
		return (1);
	if (tree->type == HEREDOC)
	{
		tree->heredoc = malloc(sizeof(t_hdc));
		process_heredoc(tree, shell, tree->heredoc);
		if (shell->exit_code == 130)
			return (1);
	}
	return (0);
}

/**
 * @brief Handles the creation and processing of a heredoc in a child process.
 *
 * Forks a child to process heredoc input and sets the shell's exit code.
 * @param tree Pointer to the AST node.
 * @param shell Pointer to the shell state structure.
 * @param heredoc Pointer to the heredoc structure to fill.
 */
void	process_heredoc(t_exec *tree, t_shell *shell, t_hdc *heredoc)
{
	pid_t	pid;
	int		exit_code;

	heredoc->fd = -1;
	heredoc->file_name = get_random_name(shell);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		ft_exit(shell, -1);
	}
	if (pid == 0)
		heredoc_child_process(tree, shell, heredoc);
	waitpid(pid, &exit_code, 0);
	if (WIFSIGNALED(exit_code))
		shell->exit_code = 128 + WTERMSIG(exit_code);
	else if (WIFEXITED(exit_code))
		shell->exit_code = WEXITSTATUS(exit_code);
}
