/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/07/03 04:50:11 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// main tokenizer function: iterates over input
// and builds a linked list of tokens
t_token	*tokenize(char *input)
{
	t_token			*head;
	t_token			*new_token;
	t_token_oprt	oprt;
	int				i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (is_operator(input[i]))
		{
			oprt = handle_operator(&input[i]);
			new_token = create_token(oprt.token, oprt.type, oprt.len);
			free(oprt.token);
			i += oprt.len;
		}
		else
			new_token = handle_word(input, &i);
		add_token(&head, new_token);
	}
	return (head);
}

/* // validar o input dos tokens
int	validate_token(t_token *tokens)
{
	t_token *prev = NULL;

	// ver se os tokens sao validos
	while (tokens)
	{ // PIPE no inicio, 2 seguidos ou no fim
		if (tokens->type == PIPE)
		{
			if (!prev || !tokens->next || tokens->next->type == PIPE)
				return (ft_printf("zsh: parse error near `||'\n"), 1);
		}
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT 
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (!tokens->next || tokens->next->type != CMD)
				return (ft_printf("zsh: parse error near `%s'\n", tokens->content), 1);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
} */

/* int	is_incomplete_input(t_token *tokens)
{
	t_token	*last;

	last = NULL;
	if (!tokens)
		return (0);
	while(tokens)
	{
		last = tokens;
		tokens = tokens->next;
	}
	if (last->type != CMD)
		return (1);
	return (0);
} */