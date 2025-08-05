/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 04:13:26 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/05 22:25:23 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// expands variable $VAR or $? found at current string position
char	*expand_dollar(t_shell *shell, char *str, int *i)
{
	char	*temp;
	char	*value;
	int		start;

	start = *i;
	(*i)++;
	if (!str[*i])
		return (ft_strdup("$"));
	if (str[*i] == '?')
		return ((*i)++, ft_itoa(shell->exit_code));
	if (!is_valid_var_start(str[*i]))
		return (ft_strdup("$"));
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;
	temp = ft_substr(str, start, *i - start);
	value = expand_var(shell, temp);
	// free no temp
	return (value);
}

// main function that processes all $ in a token and returns expanded string
char	*ft_expander(t_shell *sh, char *token)
{
	int		i;
	int		start;
	t_list	*parts;

	if (!token)
		return (NULL);
	parts = ft_lstnew(ft_strdup(""));
	i = 0;
	start = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			add_str_to_list(&parts, ft_substr(token, start, i - start));
			add_str_to_list(&parts, expand_dollar(sh, token, &i));
			start = i;
		}
		else
			i++;
	}
	add_str_to_list(&parts, ft_substr(token, start, i - start));
	// dar free no token
	return (ft_join_list_and_free(&parts, '\0'));
}

// iterates through all tokens and expands variables in CMD type tokens
void	expand_tokens(t_shell *sh)
{
	t_token	*curr;

	curr = sh->tokens;
	while (curr)
	{
		if (curr->type == CMD && curr->content)
		{
			//printf("ANTES DA EXPANSAO: %s\n", curr->content);
			curr->content = ft_expander(sh, curr->content);
			//printf("DEPOIS DA EXPANSAO: %s\n", curr->content);
		}
		curr = curr->next;
	}
}
