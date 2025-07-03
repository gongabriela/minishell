/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:23:09 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/29 17:02:02 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	char	a;

	a = (char)c;
	count = 0;
	while (s[count] != '\0')
	{
		if (s[count] == a)
			return ((char *)&s[count]);
		count++;
	}
	if (a == '\0')
		return ((char *)&s[count]);
	return (NULL);
}
