/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:20:50 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/05 17:20:50 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates the shell prompt string using env variables.
 *
 * Finds USER and HOME in env, gets hostname and cwd, and builds the prompt.
 *
 * @param env Pointer to the environment list.
 * @return Allocated prompt string, or NULL on error.
 */
char	*create_prompt(t_env *env)
{
	char	*user;
	char	*hostname;
	char	*home;
	char	*cwd;

	home = NULL;
	while (env != NULL)
	{
		if (ft_strncmp(env->key, "USER", 4) == 0)
			user = env->content;
		if (ft_strncmp(env->key, "HOME", 4) == 0) //se nao encontrar so ignora e faz o cwd sem tirar o path do home
			home = env->content;
		env = env->next;
	}
	if (!user || !home)
		return (NULL);
	hostname = get_hostname();
	if (!hostname)
		return (NULL);
	cwd = get_cwd(home);
	if (!cwd)
		return (NULL);
	return (get_full_prompt(user, hostname, cwd));
}

/**
 * @brief Gets the machine hostname from /etc/hostname.
 *
 * Opens /etc/hostname, reads the first line using get_hostname_line,
 * and extracts the hostname up to the first '.' or '\n'. Returns a newly
 * allocated string with the hostname, or NULL on error.
 *
 * @return Newly allocated hostname string, or NULL on error.
 */
char	*get_hostname(void)
{
	int		fd;
	char	*temp;
	char	*hostname;
	int		i;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (NULL);
	temp = get_hostname_line(fd);
	close(fd);
	if (!temp)
		return (NULL);
	i = 0;
	while (temp[i] != '.' && temp[i] != '\0' && temp[i] != '\n')
		i++;
	hostname = ft_substr(temp, 0, i);
	free(temp);
	if (!hostname)
		return (NULL);
	return (hostname);
}

/**
 * @brief Reads the first line from a file descriptor.
 *
 * @param fd File descriptor to read from.
 * @return Allocated string with the first line, or NULL on error.
 */
char	*get_hostname_line(int fd)
{
	char	*temp;
	char	*rest;

	temp = get_next_line(fd);
	rest = get_next_line(fd);
	while (rest != NULL)
	{
		free(rest);
		rest = get_next_line(fd);
	}
	return (temp);
}

/**
 * @brief Gets the current working directory, replacing $HOME with ~.
 *
 * @param home The HOME directory string.
 * @return Allocated cwd string, or NULL on error.
 */
char	*get_cwd(char *home)
{
	char	*temp;
	char	*cwd;

	temp = getcwd(NULL, 0);
	if (temp == NULL)
		return (NULL);
	if (ft_strncmp(temp, home, ft_strlen(home)) == 0)
	{
		if (ft_strlen(temp) > ft_strlen(home))
			cwd = ft_strjoin("~", temp + ft_strlen(home));
		else
			cwd = ft_strdup("~");
		free(temp);
	}
	else
		cwd = temp;
	return (cwd);
}

/**
 * @brief Builds the full shell prompt string.
 *
 * Concatenates user, hostname, cwd, and prompt symbols.
 *
 * @param user The username string.
 * @param hostname The hostname string (allocated).
 * @param cwd The current working directory string (allocated).
 * @return Allocated prompt string, or NULL on error.
 */
char	*get_full_prompt(char *user, char *hostname, char *cwd)
{
	char	*prompt;
	size_t	len;

	len = ft_strlen(user) + ft_strlen(hostname) + ft_strlen(cwd) + 5;
	prompt = ft_calloc(len, sizeof(char));
	if (!prompt)
		return (NULL);
	ft_strlcat(prompt, user, len);
	ft_strlcat(prompt, "@", len);
	ft_strlcat(prompt, hostname, len);
	ft_strlcat(prompt, ":", len);
	ft_strlcat(prompt, cwd, len);
	ft_strlcat(prompt, "$ ", len);
	free(hostname);
	free(cwd);
	return (prompt);
}
