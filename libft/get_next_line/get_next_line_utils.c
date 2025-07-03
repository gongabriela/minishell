/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:27:44 by adias-do          #+#    #+#             */
/*   Updated: 2024/12/04 17:16:20 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_strlen(char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (s[count])
	{
		count++;
	}
	return (count);
}

char	*get_strchr(const char *s, int c)
{
	int		count;
	char	a;

	a = (char)c;
	count = 0;
	if (!s)
		return (0);
	while (s[count])
	{
		if (s[count] == a)
			return ((char *)&s[count]);
		count++;
	}
	if (!a)
		return ((char *)&s[count]);
	return (NULL);
}

char	*get_strdup(const char *s)
{
	size_t	c;
	char	*dup;

	c = 0;
	if (!s)
		return (NULL);
	dup = (char *)malloc((get_strlen((char *)s) + 1) * (sizeof(char)));
	if (!dup)
		return (NULL);
	while (s[c])
	{
		dup[c] = s[c];
		c++;
	}
	dup[c] = '\0';
	return (dup);
}

char	*get_substr(char *s, int start, size_t len)
{
	char		*loc;
	size_t		len_max;
	size_t		c;

	c = 0;
	if (s == NULL)
		return (NULL);
	if (start >= get_strlen(s))
		return (get_strdup(""));
	len_max = get_strlen(&s[start]);
	if (len > len_max)
		len = len_max;
	loc = (char *)malloc((len + 1) * (sizeof(char)));
	if (loc == NULL)
		return (NULL);
	while (c < len)
	{
		loc[c] = s[start + 1];
		s++;
		c++;
	}
	loc[c] = '\0';
	return (loc);
}

char	*get_strjoin(char *all_line, char *buffer)
{
	int		c;
	int		i;
	char	*ln;

	c = 0;
	i = 0;
	if (!all_line)
		all_line = get_strdup("");
	if (!all_line || !buffer)
		return (NULL);
	if (get_strlen(all_line) + get_strlen(buffer) == 0)
		return (free(all_line), NULL);
	ln = malloc(sizeof(char) * (get_strlen(all_line) + get_strlen(buffer) + 1));
	if (!ln)
		return (free(all_line), NULL);
	while (all_line[c] != '\0')
	{
		ln[c] = all_line[c];
		c++;
	}
	while (buffer[i] != '\0')
		ln[c++] = buffer[i++];
	ln[c] = '\0';
	free(all_line);
	return (ln);
}
