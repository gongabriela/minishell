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

#include "../../inc/minishell.h"

/**
 * Implements the 'exit' builtin command.
 * Checks arguments, determines exit code, and exits the shell.
 *
 * @param shell Pointer to the shell state structure.
 * @param args  Arguments passed to the exit command.
 */
void	ft_exit_builtin(t_shell *shell, char **args)
{
	bool	is_non_numeric;

	is_non_numeric = false;
	if (check_exit_args(shell, args, &is_non_numeric))
		return ;
	get_exit_code(shell, args, is_non_numeric);
	ft_exit(shell, shell->exit_code);
}

/**
 * Validates the arguments passed to the 'exit' command.
 * Sets the shell's exit_code and prints errors if arguments are invalid.
 *
 * @param shell Pointer to the shell state structure.
 * @param args  Arguments passed to the exit command.
 */
int	check_exit_args(t_shell *shell, char **args, bool *is_non_numeric)
{
	int	i;

	if (!args[1])
		return (0);
	if (args[2])
	{
		error_msg("too many arguments", args[0], NULL);
		shell->exit_code = 1;
		return (1);
	}
	i = 0;
	if (args[1][0] == '-' || args[1][0] == '+')
		i++;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			error_msg("numeric argument required", args[0], args[1]);
			shell->exit_code = 2;
			*is_non_numeric = true;
			return (0);
		}
		i++;
	}
	return (0);
}

/**
 * Calculates and sets the exit code for the shell based on arguments.
 *
 * @param shell Pointer to the shell state structure.
 * @param args  Arguments passed to the exit command.
 */
void	get_exit_code(t_shell *shell, char **args, bool is_non_numeric)
{
	if (is_non_numeric == true)
		return ;
	if (!args[1])
	{
		shell->exit_code = 0;
		return ;
	}
	shell->exit_code = ft_atoi(args[1]);
	shell->exit_code = ((shell->exit_code % 256) + 256) % 256;
}
