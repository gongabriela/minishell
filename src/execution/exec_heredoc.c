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
	if (!tree)
		return ;
	if (tree->type == HEREDOC)
	{
		tree->heredoc = malloc(sizeof(t_hdc));
		process_heredoc(tree, shell, tree->heredoc);
	}
	execute_heredocs(tree->left, shell);
	execute_heredocs(tree->right, shell);
}

void	process_heredoc(t_exec *tree, t_shell *shell, t_hdc *heredoc)
{
	pid_t	pid;
	int		exit_code;

	heredoc->file_name = get_random_name(shell);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		ft_exit(shell, -1);
	}
	if (pid == 0)
	{
		heredoc->fd = open(heredoc->file_name,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (heredoc->fd < 0)
		{
			perror("open failed");
			ft_exit(shell, -1);
		}
		get_heredoc_input(tree, heredoc);
		close(heredoc->fd);
		exit(0);
	}
	waitpid(pid, &exit_code, 0);
	shell->exit_code = exit_code;
}

char	*get_random_name(t_shell *shell)
{
	static int	i = 0;
	char		*pid;
	char		*i_str;
	char		*temp;
	char		*file_name;

	pid = ft_itoa(getpid());
	temp = ft_strjoin("/tmp/.heredoc_", pid);
	if (!temp)
	{
		perror("malloc failed");
		free(pid);
		ft_exit(shell, -1);
	}
	i_str = ft_itoa(i++);
	file_name = ft_strjoin(temp, i_str);
	if (!file_name)
	{
		perror("malloc failed");
		free(pid);
		free(temp);
		ft_exit(shell, -1);
	}
	free(pid);
	free(i_str);
	free(temp);
	return (file_name);
}

void	get_heredoc_input(t_exec *tree, t_hdc *heredoc)
{
	char	*input;

	while (1)
	{
		input = readline(">");
		if (!ft_strncmp(input, tree->right->delimiter,
				ft_strlen(tree->right->delimiter)))
		{
			free(input);
			break ;
		}
		write(heredoc->fd, input, ft_strlen(input));
		write(heredoc->fd, "\n", 1);
		free(input);
	}
}

void	free_heredoc_struct(t_hdc *heredoc)
{
	if (heredoc->file_name)
	{
		unlink(heredoc->file_name);
		free(heredoc->file_name);
	}
	free(heredoc);
}
