/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   853_export_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:06:41 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/31 17:12:42 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Removes surrounding quotes from a string if present.
 *
 * Checks if the string is surrounded by matching single or double quotes
 * and removes them. If no quotes are found, returns a duplicate of the
 * original string. Used primarily in export command processing to handle
 * quoted variable values.
 *
 * @param str String to process for quote removal.
 * @return New string with quotes removed, or duplicate if no quotes found.
 */
char	*remove_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (ft_substr(str, 1, len - 2));
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
