/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:55:20 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/03 11:55:20 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Main loop of the minishell program.
 *
 * executes de minishell loop (REPL).
 * @param shell Pointer to the shell state structure.
 */
void	minishell(t_shell *shell)
{
	int	pid_index;

	while (1)
	{
		setup_signals_prompt();
		pid_index = 0;
		if (get_input(shell))
		{
			shell->tokens = tokenize(shell->input);
			expand_tokens(shell);
			process_assignments(shell);
			shell->cmd_total = get_cmd_total(shell->tokens);
			if (create_ast(shell, shell->tokens))
			{
				if (!execute_heredocs(shell->tree, shell))
					minishell_the_second(shell, &pid_index);
			}
		}
		unlink_heredocs(shell->tree);
		ft_free_shell(shell);
	}
}

void	minishell_the_second(t_shell *shell, int *pid_index)
{
	pre_execution(shell->tree, shell);
	execution(shell->tree, shell, pid_index);
	close_fds_pipes(shell);
	wait_pids(shell);
}

/**
 * @brief Reads and processes user input from the prompt.
 *
 * Creates the prompt, reads input using readline, adds it to history,
 *  and performs pre-parsing.
 * Exits the shell if input or prompt allocation fails.
 * @param shell Pointer to the shell state structure.
 * @return 1 if input is valid and ready for parsing, 0 otherwise.
 */
int	get_input(t_shell *shell)
{
	shell->prompt = create_prompt(shell);
	if (!shell->prompt)
		ft_exit(shell, -1);
	shell->input = readline(shell->prompt);
	if (!shell->input)
		ft_exit(shell, 0);
	add_history(shell->input);
	if (shell->input[0] != '\0' && pre_parsing(shell->input))
		return (1);
	return (0);
}

/**
 * @brief Closes and frees all pipe file descriptors.
 *
 * @param shell Pointer to the shell state structure.
 */
void	close_all_pipes(t_shell *shell)
{
	int	i;

	if (!shell->pipe_fds)
		return ;
	i = 0;
	while (i < shell->cmd_total - 1)
	{
		close(shell->pipe_fds[i][0]);
		close(shell->pipe_fds[i][1]);
		free(shell->pipe_fds[i]);
		i++;
	}
	free(shell->pipe_fds);
	shell->pipe_fds = NULL;
}

/**
 * @brief Waits for all child processes and updates shell->exit code.
 *
 * Waits for each process ID and sets the exit code.
 * @param shell Pointer to the shell state structure.
 */
void	wait_pids(t_shell *shell)
{
	int		status;
	int		i;
	int		newline_flag;

	newline_flag = 0;
	i = 0;
	status = 0;
	if (!shell->pids)
		return ;
	while (i < shell->cmd_total)
	{
		if (shell->pids[i] > 0)
			waitpid(shell->pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT
			&& newline_flag == 0)
			print_newline_sigint(&newline_flag);
		if (i == shell->cmd_total - 1)
		{
			if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
}
