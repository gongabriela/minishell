/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/12 12:31:52 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
