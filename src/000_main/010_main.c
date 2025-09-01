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

#include "../../inc/minishell.h"

/**
 * @brief Checks program arguments and environment validity.
 *
 * Exits if the argument count is not 1 or if the environment is missing.
 *
 * @param argc Argument count.
 * @param argv Argument vector (unused).
 * @param envp Environment variables.
 */
void	check_args(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1 || !envp || !envp[0])
		exit(1);
}

/**
 * @brief Initializes the t_shell structure fields to NULL.
 *
 * Sets all pointers in the shell struct to NULL before use.
 *
 * @param shell Pointer to the t_shell struct to initialize.
 */
void	init_structs(t_shell *shell)
{
	shell->input = NULL;
	shell->prompt = NULL;
	shell->envp = NULL;
	shell->tokens = NULL;
	shell->tree = NULL;
	shell->pipe_fds = NULL;
	shell->cmd_total = 0;
	shell->pids = NULL;
	shell->pid_index = -1;
	shell->envp = NULL;
}

void	increment_shlvl(t_shell *shell)
{
	t_env	*shlvl;
	int		value;

	shlvl = NULL;
	shlvl = search_var_in_env(shell, "SHLVL");
	if (!shlvl)
		return ;
	value = ft_atoi(shlvl->content);
	value++;
	free(shlvl->content);
	shlvl->content = ft_itoa(value);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	check_args(argc, argv, envp);
	init_structs(&shell);
	shell.exit_code = 0;
	shell.env = NULL;
	shell.pwd = NULL;
	get_env(&shell, envp);
	shell.envp = envp;
	increment_shlvl(&shell);
	minishell(&shell);
	return (0);
}
