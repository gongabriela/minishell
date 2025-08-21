/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   530_tokenizer_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:26:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/21 17:46:06 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_assignment(char *input, int start, int end)
{
	int	i;

	i = start;
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (false);
	while (i < end)
	{
		if (input[i] == '=')
			return (i > start);
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (false);
		i++;
	}
	return (false);
}

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
	int		start;
	char	quote_state;
	t_token	*token;

	quote_state = 0;
	start = *i;
	while (input[*i])
	{
		quote_state = update_quote_state(quote_state, input[*i]);
		if (!quote_state && (input[*i] == ' ' || input[*i] == '\t'
				|| is_operator(input[*i])))
			break ;
		(*i)++;
	}
	token = create_token(&input[start], CMD, *i - start);
	if (token)
		token->is_assign = is_assignment(input, start, *i);
	return (token);
}

/**
 * @brief Initializes the array of token operators.
 *
 * Sets the length, token string, and token type for each operator
 * supported by the tokenizer, including redirections and pipes.
 *
 * @param oprt Array of t_oprt to initialize.
 */
void	init_token_ops(t_oprt *oprt)
{
	oprt[0] = (t_oprt){2, "<<", HEREDOC};
	oprt[1] = (t_oprt){1, "<", REDIR_IN};
	oprt[2] = (t_oprt){2, ">>", APPEND};
	oprt[3] = (t_oprt){1, ">", REDIR_OUT};
	oprt[4] = (t_oprt){1, "|", PIPE};
	oprt[5] = (t_oprt){0, NULL, 0};
}

/**
 * @brief Identifies and returns a token operator from the input.
 *
 * Compares the start of the input string with known operators,
 * returning the matching operator token if found.
 * Returns a default CMD token if no operator matches.
 *
 * @param input Input string starting at the potential operator.
 * @return t_oprt Struct containing length, token string, and type.
 */
t_oprt	handle_operator(char *input)
{
	int		i;
	t_oprt	oprt[6];
	t_oprt	result;

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
