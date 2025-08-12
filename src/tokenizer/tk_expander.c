/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 04:13:26 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/12 01:39:13 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Expands a dollar variable ($VAR or $?) found at the current string position.
 *
 * Advances the index pointer accordingly.
 * Returns the expanded string or "$" if no valid variable is found.
 *
 * @param shell Pointer to the shell struct (to access environment and exit code).
 * @param str Input string to parse.
 * @param i Pointer to current index in the input string (gets updated).
 * @return Newly allocated expanded string.
 */
char	*expand_dollar(t_shell *shell, char *str, int *i)
{
	char	*temp;
	char	*value;
	int		start;

	start = *i;
	(*i)++;
	if (!str[*i])
		return (ft_strdup("$"));
	if (str[*i] == '?')
		return ((*i)++, ft_itoa(shell->exit_code));
	if (!is_valid_var_start(str[*i]))
		return (ft_strdup("$"));
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;
	temp = ft_substr(str, start, *i - start);
	value = expand_var(shell, temp);
	free(temp);
	return (value);
}

/**
 * @brief Extracts the literal string inside single quotes, no expansion inside.
 *
 * Advances index pointer past the closing quote.
 *
 * @param str Input string to parse.
 * @param i Pointer to current index in the input string (gets updated).
 * @return Newly allocated string from inside the single quotes.
 */
char	*expand_single_quotes(char *str, int *i)
{
	int		start;
	char	*ret;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	ret = ft_substr(str, start, *i - start);
	if (str[*i] == '\'')
		(*i)++;
	return (ret);
}

/**
 * @brief Joins two strings and frees one or both depending on the free_flag.
 *
 * free_flag: 1 = free s1, 2 = free s2, 3 = free both, 0 = free none.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @param free_flag Controls which strings to free.
 * @return Newly allocated joined string.
 */
char	*ft_strjoin_free(char *s1, char *s2, int free_flag)
{// tirar daqui e ajustar
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (free_flag == 1 || free_flag == 3)
		free(s1);
	if (free_flag == 2 || free_flag == 3)
		free(s2);
	return (joined);
}

/**
 * @brief Expands a string inside double quotes, expanding $variables inside.
 *
 * Advances index pointer past the closing double quote.
 *
 * @param shell Pointer to the shell struct (to access environment and exit code).
 * @param str Input string to parse.
 * @param i Pointer to current index in the input string (gets updated).
 * @return Newly allocated expanded string.
 */
char	*expand_double_quotes(t_shell *shell, char *str, int *i)
{
	char	*result;
	char	*temp;
	int		start;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			temp = ft_substr(str, start, *i - start);
			result = ft_strjoin_free(result, temp, 3);
			temp = expand_dollar(shell, str, i);
			result = ft_strjoin_free(result, temp, 3);
			start = *i;
		}
		else
			(*i)++;
	}
	temp = ft_substr(str, start, *i - start);
	result = ft_strjoin_free(result, temp, 3);
	if (str[*i] == '"')
		(*i)++;
	return (result);
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
		if (token[i] == '$')
		{
			add_str_to_list(&parts, ft_substr(token, start, i - start));
			add_str_to_list(&parts, expand_dollar(sh, token, &i));
			start = i;
		}
		else if (token[i] == '\'')
		{
			add_str_to_list(&parts, ft_substr(token, start, i - start));
			add_str_to_list(&parts, expand_single_quotes(token, &i));
			start = i;
		}
		else if (token[i] == '\"')
		{
			add_str_to_list(&parts, ft_substr(token, start, i - start));
			add_str_to_list(&parts, expand_double_quotes(sh, token, &i));
			start = i;
		}
		else
			i++;
	}
	add_str_to_list(&parts, ft_substr(token, start, i - start));
	return (ft_join_list_and_free(&parts, '\0'));
}

/**
 * @brief Iterates through all tokens and expands variables only in CMD type tokens.
 *
 * Frees the old token content and replaces it with the expanded version.
 *
 * @param sh Pointer to the shell struct containing the tokens list.
 */
void	expand_tokens(t_shell *sh)
{
	char	*temp;
	t_token	*curr;

	curr = sh->tokens;
	while (curr)
	{
		if (curr->type == CMD && curr->content)
		{
			temp = ft_expander(sh, curr->content);
			free(curr->content);
			curr->content = temp;
		}
		curr = curr->next;
	}
}
