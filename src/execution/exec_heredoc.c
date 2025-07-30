/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:26:06 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/07/16 17:26:06 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_heredocs(t_exec *tree, t_shell *shell)
{
	int	fd;

	if (!tree)
		return ;
	if (tree->type == HEREDOC)
	{
		//criar arquivo heredoc
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			printf("-bash: %s: Permission denied\n", file);
		else
			perror("pipex");
	}
		//guardar o fd do arquivo como stdin do tree->left
		//chamar o prompt ate o delimiter e guardar o input no arquivo heredoc
	}

}