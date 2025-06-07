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

//colocar do prompt ao parsing quotes numa funcao separada para nao flodar a funcao principal
//mas nao chamar de ft_readline() kkkkk
void	minishell(t_shell *shell, char **envp)
{
	get_env(shell, envp);
	shell->prompt = create_prompt(shell->env);
	if (!shell->prompt)
		ft_error("env not found", shell); //erro ou printo um prompt qualquer? nao ter acesso a env da problemas no futuro? ou so path?
	shell->input = readline(shell->prompt);
	if (!shell->input) //quando usa ctrl + D
		printf("Error retaining input\n");
	else
		printf("you wrote this: %s\n", shell->input);
	//add_history(shell.input);
	//pre_parsing(shell.input);
	ft_free_shell(shell); //e dar reset ao mesmo tempo????
}
