/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:24:08 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/27 12:24:08 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
/**
 * @brief Checks if the export argument is a valid identifier.
 *
 * @param shell The shell state.
 * @param arg The argument to check.
 * @return 0 if valid, -1 if invalid.
 */
int	parse_export_args(t_shell *shell, char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		printf("bash: export: `%s': not a valid identifier\n", arg);
		shell->exit_code = 1;
		return (-1);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			printf("bash: export: `%s': not a valid identifier\n", arg);
			shell->exit_code = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Searches for a variable in the environment list.
 *
 * @param shell The shell state.
 * @param arg The variable name (may include '=').
 * @return Pointer to the found variable node, or NULL if not found.
 */
t_env	*search_var_in_env(t_shell *shell, char *arg)
{
	size_t	len;
	t_env	*export;

	if (ft_strchr(arg, '='))
		len = (size_t)(ft_strchr(arg, '=') - arg);
	else
		len = ft_strlen(arg);
	export = shell->env;
	while (export)
	{
		if (export->export && ft_strncmp(export->key, arg, len) == 0
			&& ft_strlen(export->key) == len)
			return (export);
		export = export->next;
	}
	return (NULL);
}

/**
 * @brief Updates the value of an existing environment variable.
 *
 * @param shell The shell state.
 * @param var The variable node to update.
 * @param arg The argument containing the new value.
 */
void	update_env_var(t_shell *shell, t_env *var, char *arg)
{
	if (ft_strchr(arg, '='))
	{
		free(var->content);
		var->content = ft_strdup(ft_strchr(arg, '=') + 1);
		var->env = true;
	}
	var->export = true;
	(void)shell;
}

/**
 * @brief Inserts a new environment variable node into the shell's env list
 * in sorted order.
 *
 * @param shell The shell state.
 * @param new The new environment variable node.
 */
void	insert_env_sorted(t_shell *shell, t_env *new)
{
	t_env	*curr;
	t_env	*prev;

	curr = shell->env;
	prev = NULL;
	while (curr && ft_strncmp(new->key, curr->key, ft_strlen(new->key) + 1) > 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
	{
		new->next = shell->env;
		shell->env = new;
	}
	else
	{
		prev->next = new;
		new->next = curr;
	}
}

/**
 * @brief Creates a new environment variable node and inserts it into the env
 * list.
 *
 * @param shell The shell state.
 * @param arg The argument containing the variable name and value.
 */
void	create_new_env_var(t_shell *shell, char *arg)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	if (ft_strchr(arg, '='))
	{
		new->key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		new->content = ft_strdup(ft_strchr(arg, '=') + 1);
		new->env = true;
	}
	else
	{
		new->key = ft_strdup(arg);
		new->content = NULL;
		new->env = false;
	}
	new->export = true;
	new->next = NULL;
	insert_env_sorted(shell, new);
}
