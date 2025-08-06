/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:26:25 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/16 17:26:25 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_external_cmd(t_exec *tree, t_shell *shell, int pid_index)
{
	char	*path;

	path = get_cmd_path(tree->cmd, shell);
	if (!path)
		return ;
	shell->pids[pid_index] = fork();
	if (shell->pids[pid_index] < 0)
	{
		perror("Fork failed");
		shell->exit_code = 1;
		return ;
	}
	if (shell->pids[pid_index] == 0)
	{
		if (execve(path, tree->cmd, shell->envp) == -1)
		{
			perror("Execution failed");
			free(path);
			ft_exit(shell, 1);
		}
	}
	free(path);
}
