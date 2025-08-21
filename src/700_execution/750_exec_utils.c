/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   750_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:51:47 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/21 11:36:11 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_envp(t_shell *shell)
{
	t_env *env;
	int	i;

	i = 0;
	env = shell->env;
	while (env)
	{
		i++;
		env = env->next;
	}
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ft_memset(shell->envp, 0, sizeof(char *) * (i + 1));
	copy_envp_values(shell->envp, shell->env);
}

void	copy_envp_values(char **envp, t_env *env)
{
	int		i;
	char	*temp;

	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(temp, env->content);
		free(temp);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
}

void	free_envp_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	free_exit_child(t_shell *shell, int exit_code)
{
	ft_free_shell(shell);
	free_struct_env(shell->env);
	if (shell->pwd != NULL)
		free(shell->pwd);
	exit(exit_code);
}