/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:19:45 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/30 14:39:56 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*loc;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	loc = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!loc)
		return (NULL);
	ft_strlcpy(loc, s1, len_s1 + 1);
	ft_strlcat(loc, s2, len_s1 + len_s2 + 1);
	return (loc);
}
