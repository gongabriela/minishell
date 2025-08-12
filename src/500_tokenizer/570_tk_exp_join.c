/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_exp_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:20:36 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/12 11:44:29 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Calculates the total length needed to join all strings in the list.
 *
 * Includes space for separator characters between strings if sep is not zero.
 *
 * @param lst Pointer to the head of the linked list containing strings.
 * @param sep Separator character to be placed between strings (0 for none).
 * @return Total length required for the joined string.
 */
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

/**
 * @brief Builds a single concatenated string from all list elements.
 *
 * Copies each string and inserts the separator character between 
 * elements if sep is not zero.
 * Allocates memory for the joined string which must be freed by the caller.
 *
 * @param lst Pointer to the head of the linked list containing strings.
 * @param sep Separator character to be inserted between strings (0 for none).
 * @param total Total length of the resulting string (pre-calculated).
 * @return Newly allocated joined string, or NULL on allocation failure.
 */
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

/**
 * @brief Joins all strings in the list into a single string and frees the list.
 *
 * Uses count_total_len and build_joined_str internally.
 * Frees the list nodes and their string contents after joining.
 *
 * @param lst Double pointer to the head of the linked list (will be 
 * set to NULL).
 * @param sep Separator character to insert between strings (0 for none).
 * @return Newly allocated joined string, or NULL if list is 
 * empty or allocation fails.
 */
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

/**
 * @brief Joins two strings and frees one or both depending on the free_flag.
 *
 * free_flag: 1 = free s1, 2 = free s2, 3 = free both, 0 = free none.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @param free_flag Controls which strings to free.
 * @return Newly allocated joined string.
 */
char	*ft_strjoin_free(char *s1, char *s2, int free_flag)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (free_flag == 3)
		free(s1);
	if (free_flag == 3)
		free(s2);
	return (joined);
}
