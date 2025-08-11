/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 04:13:26 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/11 13:47:01 by adias-do         ###   ########.fr       */
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
	free(temp);
	return (value);
}

char	*expand_single_quotes(char *str, int *i)
{
	int		start;
	char	*ret;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	ret = ft_substr(str, start, *i - start);
	if (str[*i] == '\'')
		(*i)++;
	return (ret);
}

char *ft_strjoin_free(char *s1, char *s2, int free_flag) 
{// tirar daqui e ajustar
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (free_flag == 1 || free_flag == 3)
		free(s1);
	if (free_flag == 2 || free_flag == 3)
		free(s2);
	return (joined);
}

char	*expand_double_quotes(t_shell *shell, char *str, int *i)
{
	char	*result;
	char	*temp;
	int		start;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			temp = ft_substr(str, start, *i - start);
			result = ft_strjoin_free(result, temp, 3);
			temp = expand_dollar(shell, str, i);
			result = ft_strjoin_free(result, temp, 3);
			start = *i;
		}
		else
			(*i)++;
	}
	temp = ft_substr(str, start, *i - start);
	result = ft_strjoin_free(result, temp, 3);
	if (str[*i] == '"')
		(*i)++;
	return (result);
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
		else if (token[i] == '\'')
		{
			add_str_to_list(&parts, ft_substr(token, start, i - start));
			add_str_to_list(&parts, expand_single_quotes(token, &i));
			start = i;
		}
		else if (token[i] == '\"')
		{
			add_str_to_list(&parts, ft_substr(token, start, i - start));
			add_str_to_list(&parts, expand_double_quotes(sh, token, &i));
			start = i;
		}
		else
			i++;
	}
	add_str_to_list(&parts, ft_substr(token, start, i - start));
	return (ft_join_list_and_free(&parts, '\0'));
}

// iterates through all tokens and expands variables in CMD type tokens
void	expand_tokens(t_shell *sh)
{
	char	*temp;
	t_token	*curr;

	curr = sh->tokens;
	while (curr)
	{
		if (curr->type == CMD && curr->content)
		{
			printf("ANTES DA EXPANSAO: %s\n", curr->content); // delete
			temp = ft_expander(sh, curr->content);
			free(curr->content);
			curr->content = temp;
			printf("DEPOIS DA EXPANSAO: %s\n", curr->content); // delete
		}
		curr = curr->next;
	}
}
