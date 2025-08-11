/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:46:30 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/24 16:46:30 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Searches for and returns the value of an environment variable in the
 * linked list.
 *
 * Iterates through the linked list of environment variables (t_env) and compares
 * the keys.
 * Returns a pointer to the value (content) of the variable if found, or NULL if
 * not found.
 *
 * @param env Linked list of environment variables.
 * @param key Name of the variable to search for.
 * @return Pointer to the value of the variable, or NULL if not found.
 */
char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}
