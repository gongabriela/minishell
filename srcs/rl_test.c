/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:18:33 by adias-do          #+#    #+#             */
/*   Updated: 2025/05/30 18:45:51 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*rl;

	while (1)
	{
		rl = readline("minishell$ ");
		ft_printf("%s\n", rl);
		if (strcmp(rl, "oi") == 0)
		{
			ft_printf("minishell$ ok\n");
			free(rl);
			exit(0);
		}
		read_input(rl);
		free(rl);
	}
	return (0);
}
