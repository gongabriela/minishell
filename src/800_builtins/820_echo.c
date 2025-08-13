/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   820_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:44:30 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/12 16:28:02 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks for the presence of the -n flag in echo arguments.
 *
 * Iterates through the args to detect one or more -n flags,
 * which suppress the trailing newline.
 * Sets n_flag to 1 if found.
 * @param n_flag Pointer to the flag variable to set if -n is present.
 * @param args Array of argument strings.
 * @return The index of the first non-flag argument.
 */
int	check_n_flag(int *n_flag, char **args)
{
	int	i;
	int	j;

	*n_flag = 0;
	i = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		i++;
		*n_flag = 1;
	}
	return (i);
}

/**
 * @brief Implements the echo builtin command.
 *
 * Prints the args to stdout, separated by spaces.
 * If the -n flag is not present, prints a trailing newline.
 * Sets the shell's exit code to 0.
 * @param shell Pointer to the shell state structure.
 * @param args Array of argument strings.
 */
void	echo(t_shell *shell, char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = check_n_flag(&n_flag, args);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	shell->exit_code = 0;
}
