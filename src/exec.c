/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:04:39 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/09 10:04:39 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execution(t_exec *tree, t_shell *shell)
{
	if (tree->type == CMD)
	{
		if (is_builtin(tree->cmd))
			execute_builtin(shell, tree, tree->cmd);
		/*else
			execute_external_cmd(tree, shell);*/
	}
}

int	is_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_shell *shell, t_exec *tree, char **cmd)
{
	(void)tree;

	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		echo(shell, cmd);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		env(shell);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		pwd(shell);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		ft_exit_builtin(shell, cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		cd(shell, cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		export(shell, cmd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		unset(shell, cmd);
}

/*void	execute_external_cmd(t_exec *tree, t_shell *shell)
{

}*/