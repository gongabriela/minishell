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

void	reset_structs(t_shell shell)
{
	(void)shell; ///???????????????????

	shell.input = NULL;
	shell.prompt = NULL;
}

void	minishell(t_shell shell)
{
	reset_structs(shell);

	shell.prompt = create_prompt(shell.env);
	shell.input = readline(shell.prompt);
	if (!shell.input) //quando usa ctrl + D
		printf("Error retaining input\n");
	else
		printf("you wrote this: %s\n", shell.input);
	//add_history(shell.input);
	//pre_parsing(shell.input);
}

