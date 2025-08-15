/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:46:10 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/14 19:46:10 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Implements the cd builtin command.
 *
 * Handles argument parsing, error reporting, directory changing, and
 * environment updates.
 *
 * @param shell Pointer to the shell structure.
 * @param args The argument vector for the cd command.
 */
void	cd(t_shell *shell, char **args)
{
	char	*home;
	char	*oldpwd;
	char	*path;

	if (args[1][0] == '\0' && args[2] == NULL)
		return ;
	home = get_env_value_cd(shell->env, "HOME");
	oldpwd = get_env_value_cd(shell->env, "OLDPWD");
	if (cd_too_many_args(args))
		return (cd_error("too many arguments", NULL, shell, 1), (void)0);
	path = cd_get_path(args, home, oldpwd);
	if (!path)
	{
		if (!args[1] || args[1][0] == '~')
			return (cd_error("HOME not set", NULL, shell, 1), (void)0);
		if (!ft_strncmp(args[1], "-", 2))
			return (cd_error("OLDPWD not set", NULL, shell, 1), (void)0);
	}
	if (chdir(path) == -1)
		cd_error("No such file or directory", path, shell, 1);
	else
		update_pwd_env(shell, shell->pwd);
	free(path);
}

