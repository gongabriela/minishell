/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   550_tk_exp_dolar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:06:48 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/16 06:07:25 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Expands a dollar variable ($VAR or $?) found at the current
 * string position.
 *
 * Advances the index pointer accordingly.
 * Returns the expanded string or "$" if no valid variable is found.
 *
 * @param shell Pointer to the shell struct (to access environment and
 * exit code).
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
	if (str[*i] == '$')
		return ((*i)++, ft_itoa(getpid()));
	if (str[*i] == '0')
		return ((*i)++, ft_strdup("minishell"));
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
