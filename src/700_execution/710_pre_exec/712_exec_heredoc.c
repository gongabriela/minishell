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
void	execute_heredocs(t_exec *tree, t_shell *shell)
{
	if (!tree)
		return ;
	execute_heredocs(tree->left, shell);
	execute_heredocs(tree->right, shell);
	if (tree->type == HEREDOC)
	{
		tree->heredoc = malloc(sizeof(t_hdc));
		process_heredoc(tree, shell, tree->heredoc);
	}
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

	heredoc->file_name = get_random_name(shell);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		ft_exit(shell, -1);
	}
	if (pid == 0)
		heredoc_child_process(tree, shell, heredoc);
	waitpid(pid, &exit_code, 0);
	shell->exit_code = exit_code;
}
