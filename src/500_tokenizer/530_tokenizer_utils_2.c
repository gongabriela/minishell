/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   530_tokenizer_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:26:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/12 15:58:49 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Extracts a word (command or argument) from the input string.
 *
 * Moves the index until it finds a space, tab, or operator, then
 * creates and returns a token representing that word.
 *
 * @param input The input string to parse.
 * @param i Pointer to the current index in the input string.
 * @return Pointer to the created token containing the word.
 */
t_token	*handle_word(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != ' '
		&& input[*i] != '\t' && !is_operator(input[*i]))
		(*i)++;
	return (create_token(&input[start], CMD, *i - start));
}

/**
 * @brief Initializes the array of token operators.
 *
 * Sets the length, token string, and token type for each operator
 * supported by the tokenizer, including redirections and pipes.
 *
 * @param oprt Array of t_token_oprt to initialize.
 */
void	init_token_ops(t_token_oprt *oprt)
{
	oprt[0] = (t_token_oprt){2, "<<", HEREDOC};
	oprt[1] = (t_token_oprt){1, "<", REDIR_IN};
	oprt[2] = (t_token_oprt){2, ">>", APPEND};
	oprt[3] = (t_token_oprt){1, ">", REDIR_OUT};
	oprt[4] = (t_token_oprt){1, "|", PIPE};
	oprt[5] = (t_token_oprt){0, NULL, 0};
}

/**
 * @brief Identifies and returns a token operator from the input.
 *
 * Compares the start of the input string with known operators,
 * returning the matching operator token if found.
 * Returns a default CMD token if no operator matches.
 *
 * @param input Input string starting at the potential operator.
 * @return t_token_oprt Struct containing length, token string, and type.
 */
t_token_oprt	handle_operator(char *input)
{
	int				i;
	t_token_oprt	oprt[6];
	t_token_oprt	result;

	i = 0;
	init_token_ops(oprt);
	while (oprt[i].token)
	{
		if (ft_strncmp(input, oprt[i].token, oprt[i].len) == 0)
		{
			result.len = oprt[i].len;
			result.token = ft_strdup(oprt[i].token);
			result.type = oprt[i].type;
			return (result);
		}
		i++;
	}
	result.len = 0;
	result.token = NULL;
	result.type = CMD;
	return (result);
}
