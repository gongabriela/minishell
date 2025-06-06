/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:44:28 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/03 11:44:28 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_shell *shell, char **envp)
{
	t_env	*node;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
			ft_error("malloc failed", shell);
		ft_memset(node, 0, sizeof(t_env));

		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		node->key = ft_substr(envp[i], 0, j);
		if (!node->key)
			ft_error("malloc failed", shell);
		if (envp[i][j] == '=')
		{
			node->content = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
			if (!node->content)
				ft_error("malloc failed", shell);
		}
		else
			node->content = NULL;
		if (ft_strncmp(node->key, "PATH", 4) == 0)
			get_cmd_paths(shell, node->content);
		ft_lstadd_back(&shell->env, node);
		i++;
	}
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	get_cmd_paths(t_shell *shell, char *path_str)
{
	if (!path_str)
		return ;
	shell->cmd_paths = ft_split(path_str, ':');
	if (!shell->cmd_paths)
		ft_error("malloc failed", shell);
}