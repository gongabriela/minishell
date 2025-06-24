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

static char	*get_env_value_cd(t_env *env, const char *key)
{
    while (env)
    {
        if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
            return (env->content);
        env = env->next;
    }
    return (NULL);
}

static void	cd_error(char *msg, char *arg)
{
    ft_putstr_fd("bash: cd: ", 2);
    ft_putstr_fd(msg, 2);
    if (arg)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(arg, 2);
    }
    ft_putstr_fd("\n", 2);
}

static int	cd_too_many_args(char **args)
{
    int	i = 0;
    while (args[i])
        i++;
    return (i > 2);
}

static char	*cd_get_path(char **args, char *home, char *oldpwd)
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

static void	update_pwd_env(t_shell *shell, char *oldpwd)
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
                free(env->content); // free old value!
                env->content = ft_strdup(oldpwd);
            }
            if (!ft_strncmp(env->key, "PWD", 4))
            {
                free(env->content); // free old value!
                env->content = ft_strdup(cwd);
            }
            env = env->next;
        }
        free(shell->pwd);
        shell->pwd = ft_strdup(cwd);
    }
}

void	cd(t_shell *shell, char **args)
{
    char	*home;
    char	*oldpwd;
    char	*path;

    home = get_env_value_cd(shell->env, "HOME");
    oldpwd = get_env_value_cd(shell->env, "OLDPWD");
    if (cd_too_many_args(args))
        return (cd_error("too many arguments", NULL), (void)0);
    path = cd_get_path(args, home, oldpwd);
    if (!path)
    {
        if (!args[1] || args[1][0] == '~')
            return (cd_error("HOME not set", NULL), (void)0);
        if (!ft_strncmp(args[1], "-", 2))
            return (cd_error("OLDPWD not set", NULL), (void)0);
    }
    if (chdir(path) == -1)
        cd_error("No such file or directory", path);
    else
        update_pwd_env(shell, shell->pwd);
    free(path);
}

