/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   910_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:08 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/12 16:28:46 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Handles SIGINT (Ctrl+C) signal during the shell prompt.
 *
 * Prints a new line and resets the input line without exiting the shell.
 * @param sig The signal number (unused).
 */
void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Sets up signal handlers for the shell prompt.
 *
 * Configures SIGINT to be handled by handle_sigint and ignores SIGQUIT.
 */
void	setup_signals_prompt(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Restores default signal handling for child processes.
 *
 * Sets SIGINT and SIGQUIT to their default behaviors in child processes.
 */
void	handle_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
