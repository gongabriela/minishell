/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/06/05 21:46:17 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* void	validate_token(char *input)
{
	// ver se os tokens sao validos
}*/

t_token	*create_token(char *content, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

// separar strings e setar tokens
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
		if (input[i] == '|')
			new_token = create_token("|", PIPE);
		else if (input[i] == '>' && input[i + 1] == '>')
			new_token = create_token(">>", APPEND);
		else if (input[i] == '<' && input[i + 1] == '<')
			new_token = create_token("<<", HEREDOC);
		else if (input[i] == '<')
			new_token = create_token("<", REDIR_IN);
		else if (input[i] == '>')
			new_token = create_token(">", REDIR_OUT);
		i++;
	}
	return (head);
}

/*
new_token = create_token("|", PIPE);
if (!head)
{
	head = new_token;
	curr = new_token;
}
else
{
	curr->next = new_token;
	curr = new_token;
}
*/

/* int	main(void)
{
	
} */