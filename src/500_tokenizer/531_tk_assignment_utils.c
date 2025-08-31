/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   531_tk_assignment_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:59:37 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/31 16:45:21 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Creates a new word token from a substring of content.
 *
 * Allocates and initializes a new CMD token with specific flags for
 * variable expansion context. Sets appropriate flags to indicate this
 * token originated from variable expansion and should be cleaned up.
 *
 * @param content Source string containing the word.
 * @param start Starting index of the word in content.
 * @param end Ending index of the word in content.
 * @return Pointer to the newly created token, or NULL on failure.
 */
static t_token	*create_word_token(char *content, int start, int end)
{
	t_token	*token;

	token = create_token(content + start, CMD, end - start);
	if (!token)
		return (NULL);
	token->was_variable = false;
	token->is_assign = false;
	token->to_del = true;
	return (token);
}

static int	get_word_end(char *content, int start)
{
	int	i;

	i = start;
	while (content[i] && content[i] != ' ' && content[i] != '\t')
		i++;
	return (i);
}

static t_token	**allocate_token_array(int word_count)
{
	t_token	**tokens;

	if (word_count == 0)
		return (NULL);
	tokens = malloc(sizeof(t_token *) * (word_count + 1));
	return (tokens);
}

/**
 * @brief Fills the token array by parsing words from content string.
 *
 * Iterates through the content string, skips whitespace, identifies
 * word boundaries, and creates tokens for each word found. The process
 * continues until all content is processed.
 *
 * @param content String to parse for words.
 * @param tokens Pre-allocated array to fill with new tokens.
 */
static void	fill_token_array(char *content, t_token **tokens)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (content[i])
	{
		i = skip_whitespace(content, i);
		if (!content[i])
			break ;
		start = i;
		i = get_word_end(content, start);
		tokens[j] = create_word_token(content, start, i);
		if (!tokens[j])
			return ;
		j++;
	}
	tokens[j] = NULL;
}

/**
 * @brief Splits token content into multiple tokens based on whitespace.
 *
 * Performs word splitting on expanded variable content, creating separate
 * tokens for each word. This is essential for proper command parsing when
 * variables expand to multiple arguments.
 *
 * @param content String to split into individual word tokens.
 * @return Array of token pointers, NULL-terminated, or NULL on failure.
 */
t_token	**split_token_content(char *content)
{
	int		word_count;
	t_token	**tokens;

	word_count = count_words(content);
	tokens = allocate_token_array(word_count);
	if (!tokens)
		return (NULL);
	fill_token_array(content, tokens);
	return (tokens);
}
