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

#include "minishell.h"

int	get_input(t_shell *shell)
{
		shell->prompt = create_prompt(shell->env);
		if (!shell->prompt)
			ft_error("error creating prompt", shell); //transformar em ft_exit, e so retornar erro se for o caso...
		shell->input = readline(shell->prompt);
		if (!shell->input)
		{
			ft_free_shell(shell);
			rl_clear_history(); //so chamar essa funcao se sair do programa! se usar o exit(). nao juntar com o ft_free_shell
			exit(1);
		}
		if (pre_parsing(shell->input))
			return (1);
		return (0);
}
void	minishell(t_shell *shell, char **envp)
{
	while (1)
	{
		//handle_signals();
		get_env(shell, envp);
		if (get_input(shell))
			printf("proceed to parsing\n");
		/*if (parsing)
			printf("proceed to execution\n");
		execution()*/
		ft_free_shell(shell); //transformar num ft_reset? free, = NULL, reset nos pipes, etc!
	}
}
