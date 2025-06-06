/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:44:13 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/03 11:44:13 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_args(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1 || !envp || !envp[0])
		exit(1);
}

void	init_structs(t_shell *shell)
{
	shell->env = NULL;
	shell->cmd_paths = NULL;
	shell->input = NULL;
	shell->prompt = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	check_args(argc, argv, envp);
	init_structs(&shell);
	minishell(&shell, envp);
	return (0);
}
