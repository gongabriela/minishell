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

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_shell(t_shell *shell)
{
	t_env	*tmp;
	t_env	*curr;

	curr = shell->env;
	while (curr)
	{
		tmp = curr->next;
		free(curr->key);
		free(curr->content);
		free(curr);
		curr = tmp;
	}
	ft_free_split(shell->cmd_paths);
}