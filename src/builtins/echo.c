/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:44:30 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/27 12:20:51 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_n_flag(int *n_flag, char **args)
{
	int	i;
	int	j;

	*n_flag = 0;
	i = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		i++;
		*n_flag = 1;
	}
	return (i);
}

void	echo(t_shell *shell, char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = check_n_flag(&n_flag, args);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	shell->exit_code = 0;
}
