/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   533_tk_assignment_utils_3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:11:42 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/31 16:32:44 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*get_prev_token(t_token *head, t_token *target)
{
	t_token	*curr;

	curr = head;
	if (head == target)
		return (NULL);
	while (curr && curr->next != target)
		curr = curr->next;
	return (curr);
}

bool	was_quoted(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 2)
	{
		if ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\''))
			return (true);
	}
	return (false);
}

int	skip_whitespace(char *content, int i)
{
	while (content[i] && (content[i] == ' ' || content[i] == '\t'))
		i++;
	return (i);
}

int	count_words(char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		str++;
	}
	return (count);
}
