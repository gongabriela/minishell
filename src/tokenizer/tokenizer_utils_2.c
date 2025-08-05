/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:26:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/05 22:26:47 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// extracts a word (cmd or arg) from the input and returns a token
t_token	*handle_word(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != ' '
		&& input[*i] != '\t' && !is_operator(input[*i]))
		(*i)++;
	return (create_token(&input[start], CMD, *i - start));
}

void	init_token_ops(t_token_oprt *oprt)
{
	oprt[0] = (t_token_oprt){2, "<<", HEREDOC};
	oprt[1] = (t_token_oprt){1, "<", REDIR_IN};
	oprt[2] = (t_token_oprt){2, ">>", APPEND};
	oprt[3] = (t_token_oprt){1, ">", REDIR_OUT};
	oprt[4] = (t_token_oprt){1, "|", PIPE};
	oprt[5] = (t_token_oprt){0, NULL, 0};// end of array
}

// checks for special operator tokens:
// (|, <, >, >>, <<)
// and returns the matching token
t_token_oprt	handle_operator(char *input)
{
	int				i;
	t_token_oprt	oprt[6];  // 5 oprts + NULL
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