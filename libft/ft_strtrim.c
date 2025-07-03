/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:43:30 by adias-do          #+#    #+#             */
/*   Updated: 2024/10/31 15:46:15 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		c;
	int		i;
	int		len_s1;
	char	*loc;

	i = 0;
	c = 0;
	len_s1 = ft_strlen(s1);
	while (s1[c] && ft_strchr(set, s1[c]))
		c++;
	while (len_s1 > c && ft_strchr(set, s1[len_s1 - 1]))
		len_s1--;
	loc = (char *)malloc((len_s1 - c + 1) * sizeof(char));
	if (!loc)
		return (NULL);
	while (c < len_s1)
		loc[i++] = s1[c++];
	loc[i] = '\0';
	return (loc);
}
