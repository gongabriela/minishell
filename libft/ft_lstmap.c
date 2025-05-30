/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:04:10 by adias-do          #+#    #+#             */
/*   Updated: 2024/11/08 12:09:35 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*new;
	void	*cfun;

	new = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		cfun = (*f)(lst->content);
		map = ft_lstnew(cfun);
		if (!map)
		{
			del(cfun);
			ft_lstclear(&new, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new, map);
		lst = lst->next;
	}
	return (new);
}
