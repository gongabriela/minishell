/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:05 by adias-do          #+#    #+#             */
/*   Updated: 2024/12/04 17:16:43 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12
# endif

# include "../libft.h"
# include <unistd.h>
# include <stdlib.h>

int		get_strlen(char *s);
char	*get_strchr(const char *s, int c);
char	*get_strdup(const char *s);
char	*get_substr(char *s, int start, size_t len);
char	*get_strjoin(char *f_line, char *buffer);
char	*get_next_line(int fd);

#endif
