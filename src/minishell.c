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
	while (1)
	{
		if (get_input(shell))
			shell->tokens = tokenize(shell->input);
		shell->cmd_total = get_cmd_total(shell->tokens);
		create_ast(shell, shell->tokens);
		pre_execution(shell->tree, shell);
		print_ast(shell->tree, 0);
		/*execution(shell->tree, shell);
		for (int i = -1; i < shell->pid_index; i++) {
			waitpid(shell->pids[i][0], &shell->exit_code, 0);
		}*/
		ft_free_shell(shell);
	}
}
//e se tiver um pipe a mais? tipo erro de sintaxe
//e se tiver pipe duplo? tipo | | ls
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