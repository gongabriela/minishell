/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   530_assignment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 05:23:40 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/31 14:16:59 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*search_any_var_in_env(t_shell *shell, char *key)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	create_assignment_var(t_shell *shell, char *key, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key);
	new_var->content = ft_strdup(value);
	new_var->export = false;
	new_var->env = true;
	new_var->next = shell->env;
	shell->env = new_var;
}

void	handle_assignment(t_shell *shell, char *assignment_str)
{
	char	*key;
	char	*value;
	char	*equal_pos;
	char	*expanded_value;
	t_env	*var;

	equal_pos = ft_strchr(assignment_str, '=');
	if (!equal_pos)
		return ;
	key = ft_substr(assignment_str, 0, equal_pos - assignment_str);
	value = ft_strdup(equal_pos + 1);
	expanded_value = ft_expander(shell, value);
	var = search_any_var_in_env(shell, key);
	if (var)
	{
		free(var->content);
		var->content = ft_strdup(expanded_value);
		var->env = true;
	}
	else
		create_assignment_var(shell, key, expanded_value);
	free(key);
	free(value);
	free(expanded_value);
}

static void	remove_assignment_token(t_shell *shell, t_token *curr,
			t_token *prev, t_token *next)
{
	handle_assignment(shell, curr->content);
	if (prev)
		prev->next = next;
	else
		shell->tokens = next;
	free(curr->content);
	free(curr);
}

void	process_assignments(t_shell *shell)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;
	bool	after_command;

	prev = NULL;
	curr = shell->tokens;
	after_command = false;
	while (curr)
	{
		next = curr->next;
		if (curr->type == CMD && !curr->is_assign)
			after_command = true;
		if (curr->type == PIPE || curr->type == REDIR_IN
			|| curr->type == REDIR_OUT || curr->type == APPEND
			|| curr->type == HEREDOC)
			after_command = false;
		if (curr->is_assign && !after_command)
			remove_assignment_token(shell, curr, prev, next);
		else
			prev = curr;
		curr = next;
	}
}
