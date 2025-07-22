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
	return(pipe_fds);
}

//i = shell->cmd_total - 1 -> i = 1;
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
	i = create_pipes(shell, tree->right,pipe_fds, i);
	return (i);
}

int	get_redir_info_pipes(t_shell *shell, t_exec *tree, int **pipe_fds, int cmd)
{
	if (!tree)
		return (cmd);
	if (tree->type == PIPE)
	{
		tree->left->stdout = pipe_fds[cmd][0];
		printf("Pipe left: %d\n", tree->left->stdout);
		tree->right->stdin = pipe_fds[cmd][0];
		printf("Pipe right: %d\n", tree->right->stdin);
		cmd--;
	}
	cmd = get_redir_info_pipes(shell, tree->left, pipe_fds, cmd);
	cmd = get_redir_info_pipes(shell, tree->right, pipe_fds, cmd);
	return (cmd);
}

void	ft_free_pipes(int **pipe_fds, int cmd_total)
{
	int	i;

	if (!pipe_fds)
		return ;
	i = 0;
	while ( i < cmd_total - 1)
	{
		if (pipe_fds[i])
			free(pipe_fds[i]);
		i++;
	}
	free(pipe_fds);
}