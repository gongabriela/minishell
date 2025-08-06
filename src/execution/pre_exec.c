/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:28:31 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/21 11:28:31 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	**init_pipes(t_shell *shell)
{
	int	**pipe_fds;
	int	i;

	pipe_fds = malloc(sizeof(int *) * (shell->cmd_total - 1));
	if (!pipe_fds)
		perror("malloc failed");
	i = shell->cmd_total - 2;
	while (i >= 0)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!pipe_fds[i])
			perror("malloc failed");
		ft_memset(pipe_fds[i], 0, sizeof(int) * 2);
		i--;
	}
	return (pipe_fds);
}

int	create_pipes(t_shell *shell, t_exec *tree, int	**pipe_fds, int i)
{
	if (!tree)
		return (i);
	if (tree->type == PIPE)
	{
		if (pipe(pipe_fds[i]) == -1)
			perror("error creating pipe");
		i--;
	}
	i = create_pipes(shell, tree->left, pipe_fds, i);
	i = create_pipes(shell, tree->right, pipe_fds, i);
	return (i);
}

void	ft_free_pipes(int **pipe_fds, int cmd_total)
{
	int	i;

	if (!pipe_fds)
		return ;
	i = 0;
	while (i < cmd_total - 1)
	{
		if (pipe_fds[i])
			free(pipe_fds[i]);
		i++;
	}
	free(pipe_fds);
}

/*void	get_redir_info(t_shell *shell, t_exec *tree)
{
	if (!tree)
		return ;
	if (tree->type == REDIR_IN)

	else if (tree->type == REDIR_OUT)

	else if (tree->type == APPEND)

	get_redir_info(shell, tree->left);
	get_redir_info(shell, tree->right);
}*/