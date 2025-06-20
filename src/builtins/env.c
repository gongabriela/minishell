/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:48:51 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/20 14:09:59 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env(t_shell *shell)
{
	print_env_list(shell->env);
	shell->exit_code = 0;
}

void	print_env_list(t_env *env)
{
	while (env)
	{
		if (env->env == true)
			printf("%s=%s\n", env->key, env->content);
		env = env->next;
	}
}

/*se o input for env + alguma coisa, desconsidera-se o "env" do input!
podemos tentar resolver isso no pre parsing...*/