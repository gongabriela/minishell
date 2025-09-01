/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   770_exec_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:00:24 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/09/01 17:17:48 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reset_stdout_builtin(int saved_stdout)
{
	if (saved_stdout > 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
