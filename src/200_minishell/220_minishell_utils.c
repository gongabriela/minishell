/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   220_minishell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:39:52 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/26 18:39:52 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fds_pipes(t_shell *shell)
{
	close_all_fds(shell->tree);
	close_all_pipes(shell);
}

void	print_newline_sigint(int *flag)
{
	write(1, "\n", 1);
	*flag = 1;
}

/**
 * @brief Counts the total number of commands separated by pipes.
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
