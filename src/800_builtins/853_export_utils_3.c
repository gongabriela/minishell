/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   853_export_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:06:41 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/31 17:06:54 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
