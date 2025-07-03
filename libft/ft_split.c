/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:53:31 by adias-do          #+#    #+#             */
/*   Updated: 2024/11/05 12:23:29 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_str(char const *s, char c);
char	*ft_array(char const *s, char c);
void	*ft_free(char **loc, int count);

char	**ft_split(char const *s, char c)
{
	char	**loc;
	int		count;

	count = 0;
	if (!s && !c)
		return (NULL);
	loc = (char **)malloc(sizeof(char *) * (ft_count_str(s, c) + 1));
	if (!loc)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			loc[count] = ft_array(s, c);
			if (!loc[count])
				return (ft_free(loc, count));
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	loc[count] = NULL;
	return (loc);
}

int	ft_count_str(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	*ft_array(char const *s, char c)
{
	int		count;
	char	*loc;

	count = 0;
	while (s[count] && s[count] != c)
		count++;
	loc = (char *)malloc((count + 1) * sizeof(char));
	if (!loc)
		return (NULL);
	count = 0;
	while (s[count] && s[count] != c)
	{
		loc[count] = s[count];
		count++;
	}
	loc[count] = '\0';
	return (loc);
}

void	*ft_free(char **loc, int count)
{
	int	c;

	c = 0;
	while (c < count)
	{
		free(loc[c]);
		c++;
	}
	free(loc);
	return (NULL);
}
