/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   714_exec_heredoc_signals.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:37:11 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/26 18:37:11 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// Singleton accessor for shell struct
t_shell	*heredoc_shell_singleton(t_shell *shell, int set)
{
	static t_shell	*instance = NULL;

	if (set)
		instance = shell;
	return (instance);
}

// Custom SIGINT handler for heredoc child
void	heredoc_sigint_handler(int sig)
{
	t_shell	*shell;

	shell = heredoc_shell_singleton(NULL, 0);
	if (sig == SIGINT && shell)
	{
		write(STDOUT_FILENO, "\n", 1);
		free_exit_child(shell, 130);
	}
}

void	heredoc_signal_setup(t_shell *shell)
{
	heredoc_shell_singleton(shell, 1);
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
