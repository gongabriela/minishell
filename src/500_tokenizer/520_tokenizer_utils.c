/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   520_tokenizer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:21:18 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/12 16:39:03 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks if a character is a valid operator.
 *
 * Returns 1 if the character is one of the recognized shell operators:
 * pipe '|', input redirection '<', or output redirection '>'.
 *
 * @param c Character to check.
 * @return 1 if valid operator, 0 otherwise.
 */
int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/**
 * @brief Creates a new token with given content and type.
 *
 * Allocates memory for a token, copies the substring for content,
 * sets token type, length, and whether content should be freed later.
 *
 * @param str String to copy the content from.
 * @param type Token type to assign.
 * @param len Length of the substring to copy.
 * @return Pointer to the newly created token, or NULL if allocation fails.
 */
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

/**
 * @brief Adds a new token to the end of the token linked list.
 *
 * If the list is empty, sets the new token as the head.
 * Otherwise, traverses to the end and appends the new token.
 *
 * @param list Pointer to the head of the token list.
 * @param new_token Token to add.
 */
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

/**
 * @brief Adds a token to the list and frees operator token string.
 *
 * Calls add_token to append the token, then frees the token string
 * inside the auxiliary t_oprt struct to avoid memory leaks.
 *
 * @param list Pointer to the token list.
 * @param token Token to add.
 * @param oprt Auxiliary operator token struct whose string will be freed.
 */
void	add_token_and_free(t_token **list, t_token *token, t_oprt *oprt)
{
	add_token(list, token);
	if (oprt->token)
		free(oprt->token);
}

/**
 * @brief Updates the current quote parsing state.
 *
 * Toggles quote state when encountering matching quote characters,
 * or sets quote state when entering quotes.
 *
 * @param quote_state Current quote state (0 for no quote).
 * @param curr_char Current character being parsed.
 * @return Updated quote state.
 */
char	update_quote_state(char quote_state, char curr_char)
{
	if ((quote_state == '\'' && curr_char == '\'')
		|| (quote_state == '\"' && curr_char == '\"'))
		return (0);
	if (quote_state == 0 && (curr_char == '\'' || curr_char == '\"'))
		return (curr_char);
	return (quote_state);
}
