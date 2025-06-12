/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:44:43 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/03 11:44:43 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	print_env_list(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->content);
		env = env->next;
	}
}

void	print_cmd_paths(char **paths)
{
	int	i = 0;

	if (!paths)
		return;
	while (paths[i])
	{
		printf("PATH[%d]: %s\n", i, paths[i]);
		i++;
	}
}
