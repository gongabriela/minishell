/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:34:06 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/29 18:24:08 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	c;

	c = 0;
	dest = (char *)malloc((ft_strlen(s) + 1) * (sizeof(char)));
	if (dest == NULL)
		return (NULL);
	while (s[c] != '\0')
	{
		dest[c] = s[c];
		c++;
	}
	dest[c] = '\0';
	return (dest);
}
