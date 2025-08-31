/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   570_tk_exp_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:34:45 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/20 17:53:55 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_tilde(t_shell *shell, char *token, int *i)
{
	char	*home;

	(*i)++;
	if (!token || token[0] != '~')
		return (ft_strdup(token));
	home = get_env_value(shell->env, "HOME");
	if (!home)
		return (ft_strdup(""));
	return (ft_strdup(home));
}
