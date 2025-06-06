/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:44:55 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/03 11:44:55 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//dar free nos **cmd_path
void	free_cmd_paths(char **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

//dar free na t_env
void	free_struct_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->content);
		free(env);
		env = tmp;
	}
}

//funcao principal
void	ft_free_shell(t_shell *shell)
{

	if (shell->prompt != NULL)
		free(shell->prompt);
	if (shell->input != NULL)
		free(shell->input);
	free_struct_env(shell->env);
	free_cmd_paths(shell->cmd_paths);
	init_structs(shell);
}

void	ft_error(char *msg, t_shell *shell)
{
	perror(msg);
	ft_free_shell(shell);
	exit(-1);
}