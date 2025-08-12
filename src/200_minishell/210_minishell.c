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
 * Handles the shell prompt, input parsing, AST creation, execution, and cleanup in a loop.
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
			shell->cmd_total = get_cmd_total(shell->tokens);
			if (create_ast(shell, shell->tokens))
			{
				pre_execution(shell->tree, shell);
				execution(shell->tree, shell, &pid_index);
				close_all_pipes(shell);
				wait_pids(shell);
			}
			ft_free_shell(shell);
		}
	}
}

/**
 * @brief Reads and processes user input from the prompt.
 *
 * Creates the prompt, reads input using readline, adds it to history, and performs pre-parsing.
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
	if (pre_parsing(shell->input))
		return (1);
	return (0);
}

/**
 * @brief Counts the total number of commands separated by pipes in the token list.
 *
 * @param head Pointer to the head of the token list.
 * @return The total number of commands.
 */
int	get_cmd_total(t_token *head)
{
	int	cmds;

	cmds = 0;
	while (head)
	{
		if (head->type == PIPE)
			cmds++;
		head = head->next;
	}
	return (cmds + 1);
}

/**
 * @brief Closes and frees all pipe file descriptors used for inter-process communication.
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
 * @brief Waits for all child processes to finish and updates the shell's exit code.
 *
 * Waits for each process ID in the shell's PID array and sets the exit code based on the last command.
 * @param shell Pointer to the shell state structure.
 */
void	wait_pids(t_shell *shell)
{
	int		status;
	int		i;

	i = 0;
	while (i < shell->cmd_total)
	{
		if (shell->pids[i] > 0)
			waitpid(shell->pids[i], &status, 0);
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
