/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:43:30 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/26 15:00:18 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			c;

	c = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (c < n)
	{
		if (str1[c] != str2[c])
			return (str1[c] - str2[c]);
		c++;
	}
	return (0);
}
