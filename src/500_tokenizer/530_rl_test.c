/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   530_rl_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:18:33 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/11 16:19:52 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	print_tokens(t_token *head)
{
	while (head)
	{
		if (head->type == PIPE)
			ft_printf("PIPE -> %s\n", head->content);
		else if (head->type == CMD)
			ft_printf("CMD -> %s\n", head->content);
		else if (head->type == REDIR_IN)
			ft_printf("REDIR_IN -> %s\n", head->content);
		else if (head->type == REDIR_OUT)
			ft_printf("REDIR_OUT -> %s\n", head->content);
		else if (head->type == APPEND)
			ft_printf("APPEND -> %s\n", head->content);
		else if (head->type == HEREDOC)
			ft_printf("HEREDOC -> %s\n", head->content);
		head = head->next;
	}
}
