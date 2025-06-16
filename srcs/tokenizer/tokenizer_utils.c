/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:21:18 by adias-do          #+#    #+#             */
/*   Updated: 2025/06/16 16:59:36 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

// add a new token to the end of the token linked list
void	add_token_to_list(t_token **head, t_token **curr, t_token *new_token)
{
	if (!*head)
	{
		*head = new_token;
		*curr = new_token;
	}
	else
	{
		(*curr)->next = new_token;
		*curr = new_token;
	}
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

// checks for special operator tokens:
// (|, <, >, >>, <<)
// and returns the matching token
t_token	*handle_operator(char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (*i += 2, create_token(">>", APPEND));
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (*i += 2, create_token("<<", HEREDOC));
	if (input[*i] == '>')
		return (*i += 1, create_token(">", REDIR_OUT));
	if (input[*i] == '<')
		return (*i += 1, create_token("<", REDIR_IN));
	if (input[*i] == '|')
		return (*i += 1, create_token("|", PIPE));
	return (NULL);
}