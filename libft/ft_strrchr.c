/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:19:54 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/29 17:49:50 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	a;

	a = (char)c;
	len = ft_strlen(s);
	if (a == '\0')
		return ((char *)&s[len]);
	while (len > 0)
	{
		if (s[len - 1] == a)
			return ((char *)&s[len - 1]);
		len--;
	}
	return (NULL);
}
