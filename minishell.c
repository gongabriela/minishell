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

#include "minishell.h"

int	get_input(t_shell *shell)
{
		shell->prompt = create_prompt(shell);
		if (!shell->prompt)
		{
			ft_free_shell(shell);
			rl_clear_history();
			exit(-1);
		}
		shell->input = readline(shell->prompt);
		if (!shell->input)
		{
			ft_free_shell(shell);
			rl_clear_history();
			exit(1);
		}
		if (pre_parsing(shell->input))
			return (1);
		return (0);
}
void	minishell(t_shell *shell)
{
	while (1)
	{
		handle_signals(shell);
		if (get_input(shell))
			printf("proceed to parsing\n");
		ft_free_shell(shell);
	}
}
