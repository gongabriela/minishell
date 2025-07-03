/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:59:06 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/25 12:21:26 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	c;

	len_dst = ft_strlen(dst);
	c = 0;
	if (size <= len_dst)
		return (size + ft_strlen(src));
	while (src[c] && (len_dst + c) < (size - 1))
	{
		dst[len_dst + c] = src[c];
		c++;
	}
	dst[len_dst + c] = '\0';
	return (len_dst + ft_strlen(src));
}
