/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:40:25 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/26 17:22:49 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_lit;

	len_lit = ft_strlen(little);
	if (*little == '\0')
		return ((char *) big);
	while (*big && len > 0)
	{
		if (len >= len_lit && ft_strncmp(big, little, len_lit) == 0)
			return ((char *) big);
		big++;
		len--;
	}
	return (NULL);
}
