/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:18:33 by adias-do          #+#    #+#             */
/*   Updated: 2025/07/03 04:09:03 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

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

int main(int argc, char **argv, char **envp)
{
	char    *line;
	t_token *tokens;
	t_token *curr;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		if (*line)
			add_history(line);

		tokens = tokenize(line);
		curr = tokens;
		while (curr)
		{
			printf("Token: %-10s | Type: %d\n", curr->content, curr->type);
			curr = curr->next;
		}
		while (tokens)
		{
			curr = tokens;
			tokens = tokens->next;
			free(curr->content);
			free(curr);
		}
		free(line);
	}
	return 0;
}

