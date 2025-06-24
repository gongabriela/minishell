/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:55:20 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/03 11:55:20 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_input(t_shell *shell)
{
		shell->prompt = create_prompt(shell);
		if (!shell->prompt)
			ft_exit(shell, -1);
		shell->input = readline(shell->prompt);
		if (!shell->input)
			ft_exit(shell, 0);
		add_history(input);
		if (pre_parsing(shell->input))
			return (1);
		return (0);
}

void	execute_builtin_test(t_shell *shell, char **args)
{
	if (!args || !args[0])
		return;
	if (ft_strncmp(args[0], "echo", 5) == 0)
		echo(shell, args);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		env(shell);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		pwd(shell);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		ft_exit_builtin(shell, args);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		cd(shell, args);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		export(shell, args);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		unset(shell, args);
	else
		printf("Comando builtin não reconhecido: %s\n", args[0]);
}

void	test_builtins(t_shell *shell)
{
	char	**args;
	int		i;

	args = split_args(shell->input);
	execute_builtin_test(shell, args);
	i = 0;
	while (args && args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	minishell(t_shell *shell)
{
	while (1)
	{
		if (get_input(shell))
			test_builtins(shell);
		ft_free_shell(shell);
	}
}

