/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:15:04 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/17 13:15:04 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	delete_env_node(t_shell *shell, t_env *target)
{
	t_env	*curr;
	t_env	*prev;

	if (!shell || !shell->env || !target)
		return ;
	curr = shell->env;
	prev = NULL;
	while (curr)
	{
		if (curr == target)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env = curr->next;
			free(curr->key);
			free(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	unset_one(t_shell *shell, char *arg)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, arg, ft_strlen(env->key) + 1) == 0)
		{
			delete_env_node(shell, env);
			break ;
		}
		env = env->next;
	}
}

void	unset(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		return ((void)(shell->exit_code = 0));
	if (args[1][0] == '-' && args[1][1] != '\0')
	{
		printf("-bash: unset: %s: invalid option\n", args[1]);
		shell->exit_code = 2;
		return ;
	}
	while (args[i])
	{
		unset_one(shell, args[i]);
		i++;
	}
	shell->exit_code = 0;
}
