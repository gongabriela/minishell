/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   520_tk_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 04:13:26 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/31 17:34:44 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*exp_handler(t_shell *sh, char *token, int *i)
{
	if (token[*i] == '$')
		return (expand_dollar(sh, token, i));
	else if (token[*i] == '\'')
		return (expand_single_quotes(token, i));
	else if (token[*i] == '\"')
		return (expand_double_quotes(sh, token, i));
	else if (token[*i] == '~' && *i == 0)
		return (expand_tilde(sh, token, i));
	else
		return (NULL);
}

/**
 * @brief Main function to expand variables and quotes in a token string.
 *
 * Supports expansion of $VAR, $? and handles single and double quotes correctly.
 *
 * @param sh Pointer to shell struct.
 * @param token The input token string to expand.
 * @return Newly allocated expanded string.
 */
char	*ft_expander(t_shell *sh, char *token)
{
	int		i;
	int		start;
	t_list	*parts;

	if (!token)
		return (NULL);
	parts = ft_lstnew(ft_strdup(""));
	i = 0;
	start = 0;
	while (token[i])
	{
		if (token[i] == '$' || token[i] == '\'' || token[i] == '\"'
			|| token[i] == '~')
		{
			add_str_to_list(&parts, ft_substr(token, start, i - start));
			add_str_to_list(&parts, exp_handler(sh, token, &i));
			start = i;
		}
		else
			i++;
	}
	add_str_to_list(&parts, ft_substr(token, start, i - start));
	return (ft_join_list_and_free(&parts, '\0'));
}

/**
 * @brief Removes empty tokens from the token list.
 *
 * Iterates through the token list and removes any CMD type tokens
 * that have empty content and were originally variables. This cleanup
 * is necessary after variable expansion when some variables expand to
 * empty strings.
 *
 * @param shell Pointer to the shell struct containing the tokens list.
 */
static void	remove_empty_tokens(t_shell *shell)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	curr = shell->tokens;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (curr->type == CMD && (!curr->content || curr->content[0] == '\0')
			&& curr->was_variable)
		{
			if (prev)
				prev->next = next;
			else
				shell->tokens = next;
			free(curr->content);
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}

/**
 * @brief Handles the expansion of a single token containing variables.
 *
 * Expands variables in the token content and handles word splitting
 * if the expanded content contains spaces or tabs and was originally
 * a variable that wasn't quoted.
 *
 * @param sh Pointer to the shell struct.
 * @param curr Pointer to the current token to expand.
 * @return Pointer to the next token to process.
 */
static t_token	*handle_token_expansion(t_shell *sh, t_token *curr)
{
	char		*temp;
	t_token		*next_token;
	t_token		**new_tokens;

	curr->was_variable = (ft_strchr(curr->content, '$') != NULL);
	temp = ft_expander(sh, curr->content);
	if (temp && (ft_strchr(temp, ' ') || ft_strchr(temp, '\t'))
		&& curr->was_variable && !was_quoted(curr->content))
	{
		new_tokens = split_token_content(temp);
		next_token = curr->next;
		replace_token_with_multiple(&sh->tokens, curr,
			get_prev_token(sh->tokens, curr), new_tokens);
		free(temp);
		return (next_token);
	}
	free(curr->content);
	curr->content = temp;
	return (curr->next);
}

/**
 * @brief Iterates through all tokens and expands variables
 * only in CMD type tokens.
 *
 * Frees the old token content and replaces it with the expanded version.
 *
 * @param sh Pointer to the shell struct containing the tokens list.
 */
void	expand_tokens(t_shell *sh)
{
	t_token	*curr;

	curr = sh->tokens;
	while (curr)
	{
		if (curr->type == CMD && curr->content)
		{
			curr = handle_token_expansion(sh, curr);
			continue ;
		}
		curr = curr->next;
	}
	remove_empty_tokens(sh);
}
