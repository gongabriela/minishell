/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:37:26 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/05 10:37:26 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Retrieves the value of an environment variable by key.
 *
 * Iterates through the environment list and returns the content of the variable
 * whose key matches the provided key.
 *
 * @param env Pointer to the environment variable list.
 * @param key The name of the environment variable to search for.
 * @return Pointer to the value/content of the environment variable, or NULL if
 * not found.
 */
char	*get_env_value_cd(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Prints a formatted error message for the cd builtin to stderr.
 *
 * The message is formatted as "bash: cd: <msg>: <arg>".
 *
 * @param msg The main error message.
 * @param arg Optional argument to include in the error message (can be NULL).
 */
void	cd_error(char *msg, char *arg, t_shell *shell, int exit_code)
{
	ft_putstr_fd("bash: cd: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = exit_code;
}

/**
 * @brief Checks if too many arguments were provided to the cd command.
 *
 * @param args The argument vector for the cd command.
 * @return 1 if there are more than one argument after "cd", 0 otherwise.
 */
int	cd_too_many_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (1);
	return (0);
}

/**
 * @brief Determines the target path for the cd command.
 *
 * Handles special cases for "~", "~/", and "-" (OLDPWD).
 *
 * @param args The argument vector for the cd command.
 * @param home The value of the HOME environment variable.
 * @param oldpwd The value of the OLDPWD environment variable.
 * @return Newly allocated string with the target path, or NULL if not found.
 */
//nao ta perfeito, cd ~ e cd ~/ funciona mesmo com HOME unset
char	*cd_get_path(char **args, char *home, char *oldpwd)
{
	if (!args[1] || (args[1][0] == '~'))
	{
		if (!home)
			return (NULL);
		if (!args[1] || args[1][1] == '\0')
			return (ft_strdup(home));
		if (args[1][1] == '/')
			return (ft_strjoin(home, args[1] + 1));
		return (ft_strdup(args[1]));
	}
	if (!ft_strncmp(args[1], "-", 2))
	{
		if (!oldpwd)
			return (NULL);
		return (ft_strdup(oldpwd));
	}
	return (ft_strdup(args[1]));
}

/**
 * @brief Updates the PWD and OLDPWD environment variables after a directory
 * change.
 *
 * Also updates the shell's internal pwd field.
 *
 * @param shell Pointer to the shell structure.
 * @param oldpwd The previous working directory.
 */
void	update_pwd_env(t_shell *shell, char *oldpwd)
{
	t_env	*env;
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		env = shell->env;
		while (env)
		{
			if (!ft_strncmp(env->key, "OLDPWD", 7))
			{
				free(env->content);
				env->content = ft_strdup(oldpwd);
			}
			if (!ft_strncmp(env->key, "PWD", 4))
			{
				free(env->content);
				env->content = ft_strdup(cwd);
			}
			env = env->next;
		}
		free(shell->pwd);
		shell->pwd = ft_strdup(cwd);
	}
}
