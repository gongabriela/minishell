/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   860_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:27:14 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/12 15:48:21 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Implements the pwd builtin command.
 *
 * Prints the current working directory stored in the shell structure and sets the shell's exit code to 0.
 * @param shell Pointer to the shell state structure.
 */
void	pwd(t_shell *shell)
{
	printf("%s\n", shell->pwd);
	shell->exit_code = 0;
}
