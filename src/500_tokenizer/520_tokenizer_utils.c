/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   520_tokenizer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:21:18 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/11 16:19:52 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
