/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   520_tokenizer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:21:18 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/12 15:38:49 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// returns 1 if the character is a valid operator
int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

// creates a new token node with given content and type
t_token	*create_token(char *str, t_token_type type, int len)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_substr(str, 0, len);
	new_token->type = type;
	new_token->len = len;
	new_token->to_del = (new_token->content[0] != '\''
			&& new_token->content[0] != '\"');
	new_token->next = NULL;
	return (new_token);
}

// add a new token to the end of the token the list
void	add_token(t_token **list, t_token *new_token)
{
	t_token	*curr;

	if (!list || !new_token)
		return ;
	if (!*list)
		*list = new_token;
	else
	{
		curr = *list;
		while (curr->next)
			curr = curr->next;
		curr->next = new_token;
	}
}

// adds token to list and releases token from auxiliary structure
void	add_token_and_free(t_token **list, t_token *token, t_token_oprt *oprt)
{
	add_token(list, token);
	if (oprt->token)
		free(oprt->token);
}

// updates state of current quote (to handle parsing of quotes)
char	update_quote_state(char quote_state, char curr_char)
{
	if ((quote_state == '\'' && curr_char == '\'')
		|| (quote_state == '\"' && curr_char == '\"'))
		return (0);
	if (quote_state == 0 && (curr_char == '\'' || curr_char == '\"'))
		return (curr_char);
	return (quote_state);
}
