/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_testing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:37:18 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/13 15:37:18 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdbool.h>

/**
 * skip_spaces - Skips whitespace (spaces and tabs) in a string.
 * @s: The input string.
 *
 * Return: The number of whitespace characters skipped.
 */
int	skip_spaces(const char *s)
{
	int i = 0;

	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (i);
}

/**
 * skip_quotes - Skips over a quoted section in a string.
 * @s: The input string, starting at the opening quote.
 * @quote: The quote character (' or ").
 *
 * Return: The number of characters skipped, including both quotes.
 */
int	skip_quotes(const char *s, char quote)
{
	int i = 1;

	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

/**
 * arg_len - Calculates the length of the next argument, respecting quotes.
 * @s: The input string, starting at the argument.
 *
 * Return: The length of the argument (including quotes).
 */
int	arg_len(const char *s)
{
	int len = 0;
	int j;

	while (s[len] && s[len] != ' ' && s[len] != '\t')
	{
		if (s[len] == '\'' || s[len] == '"')
		{
			j = skip_quotes(s + len, s[len]);
			len += j;
		}
		else
			len++;
	}
	return (len);
}

/**
 * count_args - Counts the number of arguments in the input string.
 * @s: The input string.
 *
 * Return: The number of arguments found.
 */
int	count_args(const char *s)
{
	int count = 0;
	int i;

	while (*s)
	{
		i = skip_spaces(s);
		s += i;
		if (!*s)
			break ;
		count++;
		i = arg_len(s);
		s += i;
	}
	return (count);
}

/**
 * copy_arg - Copies an argument from the input string, removing quotes.
 * @s: The input string, starting at the argument.
 * @len: The length of the argument (including quotes).
 *
 * Return: A newly allocated string containing the argument (quotes removed).
 */
char	*copy_arg(const char *s, int len)
{
	char	*arg;
	int		i = 0;
	int		j = 0;
	char	quote;

	arg = (char *)malloc(len + 1);
	if (!arg)
		return (NULL);
	while (i < len)
	{
		if ((s[i] == '\'' || s[i] == '"'))
		{
			quote = s[i++];
			while (i < len && s[i] != quote)
				arg[j++] = s[i++];
			if (i < len && s[i] == quote)
				i++;
		}
		else
			arg[j++] = s[i++];
	}
	arg[j] = '\0';
	return (arg);
}

/**
 * extract_arg - Extracts the next argument from the input string.
 * @s: Pointer to the input string pointer (will be advanced).
 *
 * Return: A newly allocated string containing the next argument (quotes removed).
 */
char	*extract_arg(const char **s)
{
	int len;
	char *arg;

	*s += skip_spaces(*s);
	len = arg_len(*s);
	arg = copy_arg(*s, len);
	*s += len;
	return (arg);
}

/**
 * split_args - Splits the input string into an array of arguments, respecting quotes.
 * @s: The input string.
 *
 * Return: A NULL-terminated array of argument strings (quotes removed).
 */
char	**split_args(const char *s)
{
	int		argc;
	char	**args;
	int		i;

	argc = count_args(s);
	args = (char **)malloc(sizeof(char *) * (argc + 1));
	i = 0;
	if (!args)
		return (NULL);
	while (i < argc)
	{
		args[i] = extract_arg(&s);
		i++;
	}
	args[i] = NULL;
	return (args);
}