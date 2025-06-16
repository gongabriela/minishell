/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/06/16 17:08:03 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// main tokenizer function: iterates over input
// and builds a linked list of tokens
t_token	*tokenize(char *input)
{
	int		i;
	t_token	*head;
	t_token	*curr;
	t_token	*new_token;

	i = 0;
	head = NULL;
	curr = NULL;
	while (input[i])
	{
		while (input[i] == 32 || input[i] == '\t')
			i++;
		if (is_operator(input[i]))
			new_token = handle_operator(input, &i);
		else
			new_token = handle_word(input, &i);
		add_token_to_list(&head, &curr, new_token);
	}
	return (head);
}
// validar o input dos tokens
int	validate_token(t_token *tokens)
{
	// ver se os tokens sao validos
	while (tokens)
	{ // tenho que ver se antes tem algo
		if (tokens->type == PIPE && (!tokens->next || tokens->next->type == PIPE))
			return (ft_printf("zsh: parse error near `|'\n"));
		tokens = tokens->next;
	}
	return (0);
}

/* int	main(void)
{
	
} */