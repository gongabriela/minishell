/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_exp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:56:01 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/12 01:27:17 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks if a character is a valid start for a variable name.
 *
 * Valid start characters are alphabetic letters (a-z, A-Z) or underscore '_'.
 *
 * @param c The character to check.
 * @return int Returns non-zero (true) if valid start character, zero (false) otherwise.
 */
int	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

/**
 * @brief Checks if a character is valid inside a variable name.
 *
 * Valid characters are alphanumeric (a-z, A-Z, 0-9) or underscore '_'.
 *
 * @param c The character to check.
 * @return int Returns non-zero (true) if valid variable character, zero (false) otherwise.
 */
int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * @brief Expands a single variable token ($VAR or $?).
 *
 * If the token starts with '$' followed by a valid variable name or '?',
 * it returns the corresponding value from the environment or the last exit code.
 * Otherwise, returns a duplicate of the original token.
 *
 * @param shell Pointer to the shell structure containing environment and exit code.
 * @param token The token string starting with '$' to be expanded.
 * @return char* Newly allocated string with the expanded variable value.
 */
char	*expand_var(t_shell *shell, char *token)
{
	if (!token || token[0] != '$')
		return (ft_strdup(token));
	if (token[1] == '?')
		return (ft_itoa(shell->exit_code));
	return (ft_get_var(shell->env, token + 1));
}

/**
 * @brief Adds a new string element to the end of a linked list.
 *
 * If the content is NULL, the function does nothing.
 *
 * @param list Pointer to the pointer of the head of the linked list.
 * @param content Pointer to the string content to add to the list.
 */
void	add_str_to_list(t_list **list, void *content)
{
	t_list	*new;

	if (!content)
		return ;
	new = ft_lstnew(content);
	ft_lstadd_back(list, new);
}

/**
 * @brief Retrieves the value of an environment variable by its key.
 *
 * Iterates through the linked list of environment variables and compares keys.
 * Returns a newly allocated string with the variable content if found,
 * or an empty string if the variable does not exist.
 *
 * @param env Pointer to the head of the environment variable linked list.
 * @param key The key name of the environment variable to search for.
 * @return char* Newly allocated string with the variable's content or empty string if not found.
 */
char	*ft_get_var(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->content));
		env = env->next;
	}
	return (ft_strdup(""));
}
