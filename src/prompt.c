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

#include "../inc/minishell.h"

/**
 * @brief Creates the shell prompt string using environment variables.
 *
 * Retrieves the USER, HOME, and PWD environment variables, gets the hostname,
 * and builds the prompt string in the format: user@hostname:cwd$ .
 *
 * @param shell Pointer to the shell state (unused).
 * @return Newly allocated prompt string, or NULL on error.
 */
char	*create_prompt(void)
{
	char	*user;
	char	*hostname;
	char	*home;
	char	*pwd;

	//home == NULL;
	home = getenv("HOME");
	pwd = get_cwd(home);
	user = getenv("USER");
	if (!user)
		user = "me";
	hostname = get_hostname();
	if (!hostname)
	{
		free(pwd);
		free(user);
		return (NULL);
	}
	return (get_full_prompt(user, hostname, pwd));
}

/**
 * @brief Gets the current working directory, replacing $HOME with ~ if applicable.
 *
 * Uses the PWD environment variable if available, otherwise calls getcwd().
 * If the current directory is inside HOME, replaces the HOME prefix with '~'.
 *
 * @param home The HOME directory string.
 * @return Newly allocated cwd string, or "?" on error.
 */
char	*get_cwd(char *home)
{
	char	*temp;
	char	*cwd;

	temp = getenv("PWD");
	if (temp == NULL)
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			return ("?");
		return (cwd);
	}
	if (home != NULL && ft_strncmp(temp, home, ft_strlen(home)) == 0)
	{
		if (ft_strlen(temp) > ft_strlen(home))
			cwd = ft_strjoin("~", temp + ft_strlen(home));
		else
			cwd = ft_strdup("~");
	}
	else
		cwd = temp;
	return (cwd);
}

/**
 * @brief Gets the machine hostname from /etc/hostname.
 *
 * Reads the first line from /etc/hostname and extracts the hostname up to the
 * first '.' or newline. Returns a newly allocated string.
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
		return (perror("open failed"), NULL);
	temp = get_hostname_line(fd);
	close(fd);
	if (!temp)
		return (perror("malloc failed"), NULL);
	i = 0;
	while (temp[i] != '.' && temp[i] != '\0' && temp[i] != '\n')
		i++;
	hostname = ft_substr(temp, 0, i);
	free(temp);
	if (!hostname)
		return (perror("malloc failed"), NULL);
	return (hostname);
}

/**
 * @brief Reads the first line from a file descriptor.
 *
 * Reads all lines from the file descriptor, returns the first line as a newly
 * allocated string, and frees any additional lines.
 *
 * @param fd File descriptor to read from.
 * @return Newly allocated string with the first line, or NULL on error.
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
 * @brief Builds the full shell prompt string.
 *
 * Concatenates user, hostname, cwd, and prompt symbols into a single string.
 * Frees the hostname and cwd arguments.
 *
 * @param user The username string.
 * @param hostname The hostname string (allocated).
 * @param cwd The current working directory string (allocated).
 * @return Newly allocated prompt string, or NULL on error.
 */
char	*get_full_prompt(char *user, char *hostname, char *cwd)
{
	char	*prompt;
	size_t	len;

	len = ft_strlen(user) + ft_strlen(hostname) + ft_strlen(cwd) + 5;
	prompt = ft_calloc(len, sizeof(char));
	if (!prompt)
		return (perror("malloc failed"), NULL);
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
