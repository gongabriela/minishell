/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/13 09:52:02 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Tokenizes the input string into a linked list of tokens.
 *
 * Iterates through the input string, skipping whitespace, and
 * separates the input into tokens representing commands, arguments,
 * and operators (|, <, >, >>, <<).
 *
 * @param input The input command line string to tokenize.
 * @return Pointer to the head of the linked list of tokens.
 */
t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*new_token;
	t_oprt	oprt;
	int		i;

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
