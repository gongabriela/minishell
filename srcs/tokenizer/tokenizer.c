/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:36:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/06/13 02:57:28 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// (delete) separar outro arquivo de utils com is_operator,
// (delete) add_token_to_list (talvez mudar o nome), create_token e os handle

// returns 1 if the character is a valid operator
int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

// creates a new token node with given content and type
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

// extracts a word (cmd or arg) from the input and returns a token
t_token	*handle_word(char *input, int *i)
{
	int		start;
	char	*word;
	t_token	*new_token;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& !is_operator(input[*i]))
		(*i)++;
	word = ft_substr(input, start, *i - start);
	new_token = create_token(word, CMD);
	free(word);
	return (new_token);
}

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