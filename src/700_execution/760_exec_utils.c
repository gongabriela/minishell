/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   760_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:51:47 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/28 11:55:24 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_envp(t_shell *shell)
{
	t_env	*env;
	int		i;

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

void	check_invalid_fds(t_exec *tree, t_shell *shell)
{
	if (tree->stdin < 0 || tree->stdout < 1)
		free_exit_child(shell, 1);
}

int	redir_io_builtin(t_exec *tree, t_shell *shell)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (tree->stdout != STDOUT_FILENO)
	{
		dup2(tree->stdout, STDOUT_FILENO);
		close(tree->stdout);
	}
	if (shell->pipe_fds)
		close_unused_pipes(tree, shell);
	return (saved_stdout);
}