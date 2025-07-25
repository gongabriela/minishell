/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:02:05 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/05 10:44:26 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Implements the export builtin command.
 *
 * @param shell The shell state.
 * @param args The arguments passed to export.
 */
void	export(t_shell *shell, char **args)
{
	int		i;
	t_env	*var;

	if (args[1] == NULL)
	{
		print_export_table(shell);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (parse_export_args(shell, args[i]) == 0)
		{
			var = search_var_in_env(shell, args[i]);
			if (var == NULL)
				create_new_env_var(shell, args[i]);
			else
				update_env_var(shell, var, args[i]);
		}
		i++;
	}
}
