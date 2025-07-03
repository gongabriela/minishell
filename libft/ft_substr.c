/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:38:49 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/30 13:08:38 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*loc;
	size_t	len_max;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	len_max = ft_strlen(&s[start]);
	if (len > len_max)
		len = len_max;
	loc = (char *)malloc((len + 1) * (sizeof(char)));
	if (loc == NULL)
		return (NULL);
	ft_strlcpy(loc, &s[start], len + 1);
	return (loc);
}
