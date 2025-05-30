/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:40:35 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/29 18:01:54 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	c;

	c = 0;
	while (c < n && s1[c] == s2[c] && s1[c] && s2[c])
	{
		c++;
	}
	if (n == c)
	{
		return (0);
	}
	return ((unsigned char)s1[c] - (unsigned char)s2[c]);
}
