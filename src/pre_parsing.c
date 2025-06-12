/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:40:06 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/06 19:40:06 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

/*
 * pre_parsing - Checks the input string for unclosed single or double quotes.
 *
 * @input: The input command line string to be checked.
 *
 * This function verifies if the input string has balanced single (')
 * and double (") quotes.
 * It also adds the input to the shell history if it is not empty.
 * If any quote is unclosed, it prints a syntax error message and returns 0.
 * Returns 1 if the input is valid (all quotes are closed), or 0 otherwise.
 */
int	pre_parsing(char *input)
{
	int		i;
	int		single_quote;
	int		double_quote;

	if (!input || *input == '\0')
		return (0);
	add_history(input);
	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			single_quote++;
		else if (input[i] == '\"')
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (printf("syntax error: unclosed quotes\n"), 0);
	return (1);
}
