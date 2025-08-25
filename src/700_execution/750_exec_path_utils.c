/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   750_exec_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:16:16 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/25 16:16:16 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_cmd_path(char *path, char **cmd, t_shell *shell)
{
	if (!path)
		perror("malloc failed");
	else
	{
		shell->exit_code = 127;
		error_msg("command not found", cmd[0], NULL);
	}
}

void	check_for_slash_error_msg(int errno_code, t_shell *shell, char *cmd)
{
	if (errno_code == EACCES)
	{
		error_msg("Permission denied", cmd, NULL);
		shell->exit_code = 126;
	}
	else if (errno_code == ENOENT)
	{
		error_msg("No such file or directory", cmd, NULL);
		shell->exit_code = 127;
	}
}
