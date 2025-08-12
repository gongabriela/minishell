/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:19:46 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/14 17:19:46 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * Implements the 'exit' builtin command.
 * Checks arguments, determines exit code, and exits the shell.
 *
 * @param shell Pointer to the shell state structure.
 * @param args  Arguments passed to the exit command.
 */
void	ft_exit_builtin(t_shell *shell, char **args)
{
	check_exit_args(shell, args);
	get_exit_code(shell, args);
	ft_exit(shell, shell->exit_code);
}

/**
 * Validates the arguments passed to the 'exit' command.
 * Sets the shell's exit_code and prints errors if arguments are invalid.
 *
 * @param shell Pointer to the shell state structure.
 * @param args  Arguments passed to the exit command.
 */
void	check_exit_args(t_shell *shell, char **args)
{
	int	i;

	if (!args[1])
		return ;
	if (args[2])
	{
		perror("bash: exit: too many arguments");
		shell->exit_code = 1;
		return ;
	}
	i = 0;
	if (args[1][0] == '-')
		i++;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			perror("bash: exit: numeric argument required");
			shell->exit_code = 255;
			return ;
		}
		i++;
	}
}

/**
 * Calculates and sets the exit code for the shell based on arguments.
 *
 * @param shell Pointer to the shell state structure.
 * @param args  Arguments passed to the exit command.
 */
void	get_exit_code(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		shell->exit_code = 0;
		return ;
	}
	while (args[1][i])
		i++;
	if (i > 3)
		shell->exit_code = ft_atoi(args[1]) % 256;
	else
		shell->exit_code = ft_atoi(args[1]);
	if (shell->exit_code < 0)
		shell->exit_code = ((shell->exit_code % 256) + 256) % 256;
}
