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

#include "../inc/minishell.h"

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

void	minishell(t_shell *shell)
{
	int	pid_index;

	while (1)
	{
		pid_index = 0;
		if (get_input(shell))
		{
			shell->tokens = tokenize(shell->input);
			shell->cmd_total = get_cmd_total(shell->tokens);
			if (create_ast(shell, shell->tokens))
			{
				pre_execution(shell->tree, shell);
				//print_ast(shell->tree, 0);
				execution(shell->tree, shell, &pid_index);
				close_all_pipes(shell);
				wait_pids(shell);
			}
			ft_free_shell(shell);
		}
	}
}

int	get_cmd_total(t_token *head)
{
	int cmds;

	cmds = 0;
	while (head)
	{
		if (head->type == PIPE)
			cmds++;
		head = head->next;
	}
	return (cmds + 1);
}

void	close_all_pipes(t_shell *shell)
{
	int	i;

	if (!shell->pipe_fds)
		return ;
	for (i = 0; i < shell->cmd_total - 1; i++)
	{
		close(shell->pipe_fds[i][0]);
		close(shell->pipe_fds[i][1]);
		free(shell->pipe_fds[i]);
	}
	free(shell->pipe_fds);
	shell->pipe_fds = NULL;
}

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
