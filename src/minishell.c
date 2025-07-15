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
		if (create_ast(shell, shell->tokens))
			execution(shell->tree, shell);
		/*if (is_bultin(shell->tokens))
			test_builtins(shell);
		t_token *current = shell->tokens;
		while (current)
		{
			printf("Tokens: %s\n", current->content);
			current = current->next;
		}*/
		ft_free_shell(shell);
	}
}
