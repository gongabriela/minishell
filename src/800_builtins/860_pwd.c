/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   860_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:27:14 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/12 12:27:20 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Implements the pwd builtin command.
 *
 * Prints the current working directory stored in the shell structure.
 * sets the shell's exit code to 0.
 * @param shell Pointer to the shell state structure.
 */
void	pwd(t_shell *shell)
{
	printf("%s\n", shell->pwd);
	shell->exit_code = 0;
}
