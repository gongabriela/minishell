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

//colocar do prompt ao parsing quotes numa funcao separada para nao flodar a funcao principal, mas nao chamar de ft_readline() kkkkk
void	minishell(t_shell *shell, char **envp)
{
	while (1)
	{
		get_env(shell, envp);
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
		if (shell->input && *(shell->input) != '\0')
			add_history(shell->input); //tenho que dar free no add history?
		/*if (pre_parsing(shell->input))
			printf("not an empty line, proceed to parsing and execution\n");*/
		ft_free_shell(shell);
	}
}
