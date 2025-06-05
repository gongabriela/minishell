/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:18:33 by adias-do          #+#    #+#             */
/*   Updated: 2025/06/05 20:30:54 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tokens(t_token *head)
{
	while (head)
	{
		if (head->type == PIPE)
			ft_printf("PIPE -> %s\n", head->content);
		head = head->next;
	}
}


int	main(void)
{
	char	*rl;
	t_token	*tokens;

	while (1)
	{
		rl = readline("minishell$ ");
		ft_printf("%s\n", rl);
		if (strcmp(rl, "oi") == 0)
		{
			ft_printf("minishell$ ok\n");
			free(rl);
			exit(0);
		}
		tokens = tokenize(rl);
		print_tokens(tokens);
		free(rl);
	}
	return (0);
}
