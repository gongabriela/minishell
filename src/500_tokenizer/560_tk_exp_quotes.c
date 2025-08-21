/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   560_tk_exp_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:39:49 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/21 03:12:27 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Extracts the literal string inside single quotes, 
 * no expansion inside.
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
 * @brief Expands a string inside double quotes, expanding $variables inside.
 *
 * Advances index pointer past the closing double quote.
 *
 * @param shell Pointer to the shell struct (to access environment
 * and exit code).
 * @param str Input string to parse.
 * @param i Pointer to current index in the input string (gets updated).
 * @return Newly allocated expanded string.
 */
static char	*process_double_quotes(t_shell *shell, char *str, int *i)
{
	char	*result;
	char	*temp;
	int		start;

	result = ft_strdup("");
	if (!result)
		return (NULL);
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
	return (result);
}

char	*expand_double_quotes(t_shell *shell, char *str, int *i)
{
	char	*result;

	if (str[*i] != '"')
		return (NULL);
	(*i)++;
	result = process_double_quotes(shell, str, i);
	if (str[*i] == '"')
		(*i)++;
	return (result);
}
