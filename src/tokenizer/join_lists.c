/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:20:36 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/05 22:21:53 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// calculates total size needed to join all strings in the list
static int	count_total_len(t_list *lst, char sep)
{
	int	len;
	int	sep_count;

	len = 0;
	sep_count = 0;
	while (lst)
	{
		if (lst->content)
			len += ft_strlen(lst->content);
		sep_count++;
		lst = lst->next;
	}
	if (sep && sep_count > 1)
		len += sep_count - 1;
	return (len);
}

// builds single string by concatenating all list elements
static char	*build_joined_str(t_list *lst, char sep, int total)
{
	char	*result;
	char	*ptr;

	result = malloc(total + 1);
	if (!result)
		return (NULL);
	ptr = result;
	while (lst)
	{
		if (lst->content)
		{
			ft_memcpy(ptr, lst->content, ft_strlen(lst->content));
			ptr += ft_strlen(lst->content);
		}
		lst = lst->next;
		if (sep && lst)
			*ptr++ = sep;
	}
	*ptr = '\0';
	return (result);
}

// joins all strings in list into one and frees the list
char	*ft_join_list_and_free(t_list **lst, char sep)
{
	int		total;
	char	*joined;

	if (!lst || !*lst)
		return (NULL);
	total = count_total_len(*lst, sep);
	joined = build_joined_str(*lst, sep, total);
	ft_lstclear(lst, free);
	return (joined);
}
