/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   532_tk_assignment_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:02:10 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/31 16:47:03 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	link_new_tokens(t_token **new_tokens, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		new_tokens[i]->next = new_tokens[i + 1];
		i++;
	}
}

static void	remove_old_token(t_token **head, t_token *old_token, t_token *prev)
{
	if (prev)
		prev->next = old_token->next;
	else
		*head = old_token->next;
	free(old_token->content);
	free(old_token);
}

/**
 * @brief Replaces a single token with multiple tokens in the linked list.
 *
 * Takes an old token and replaces it with an array of new tokens, properly
 * linking them into the existing token chain. Handles edge cases like empty
 * token arrays and updates the list head if necessary.
 *
 * @param head Pointer to the head of the token list.
 * @param old_token Token to be replaced and removed.
 * @param prev Previous token in the list (NULL if old_token is head).
 * @param new_tokens Array of new tokens to insert.
 */
void	replace_token_with_multiple(t_token **head, t_token *old_token,
		t_token *prev, t_token **new_tokens)
{
	int		i;
	t_token	*last_new;

	if (!new_tokens || !new_tokens[0])
	{
		remove_old_token(head, old_token, prev);
		return ;
	}
	i = 0;
	while (new_tokens[i])
		i++;
	link_new_tokens(new_tokens, i);
	last_new = new_tokens[i - 1];
	last_new->next = old_token->next;
	if (prev)
		prev->next = new_tokens[0];
	else
		*head = new_tokens[0];
	free(old_token->content);
	free(old_token);
	free(new_tokens);
}
