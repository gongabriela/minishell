/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_exp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:56:01 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/11 03:47:39 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// checks if character can start a variable name (letter or _)
int	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

// checks if character is valid inside variable name (alphanumeric or _)
int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

// expands a single variable ($VAR or $?) to its value
char	*expand_var(t_shell *shell, char *token)
{
	if (!token || token[0] != '$')
		return (ft_strdup(token));
	if (token[1] == '?')
		return (ft_itoa(shell->exit_code));
	return (ft_get_var(shell->env, token + 1));
}

// adds string to the end of a linked list
void	add_str_to_list(t_list **list, void *content)
{
	t_list	*new;

	if (!content)
		return ;
	new = ft_lstnew(content);
	ft_lstadd_back(list, new);
}

// searches variable in environment and 
// returns its value (or empty string if not found)
char	*ft_get_var(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0) //ft_strcmp
			return (ft_strdup(env->content));
		env = env->next;
	}
	return (ft_strdup(""));
}
