/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:18:33 by adias-do          #+#    #+#             */
/*   Updated: 2025/07/04 10:38:19 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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


/*int	main(void)
{
	char	*rl;
	t_token	*tokens;

	while (1)
	{
		rl = readline("minishell$ ");
		//ft_printf("%s\n", rl);
		if (strcmp(rl, "exit") == 0)
		{
			free(rl);
			exit(0);
		}
		tokens = tokenize(rl);
		print_tokens(tokens);
		validate_token(tokens);
		free(rl);
	}
	return (0);
}*/
