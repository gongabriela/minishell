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

//melhorar as verificacoes de erro nas funcoes auxiliares
//se uma das envs dar NULL, tem que verificar quais e que nao estao para dar free e dar exit no programa
//se nao foi possivel pegar uma das env sai do programa, certo? ou so continua com o prompt mal feito?
char	*create_prompt(t_env *env)
{
	char	*user;
	char	*hostname;
	char	*home;
	char	*cwd;

	while (env != NULL)
	{
		if (ft_strncmp(env->key, "USER", 4) == 0)
			user = ft_strdup(env->content);
		if (ft_strncmp(env->key, "HOME", 4) == 0)
			home = ft_strdup(env->content);
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

char	*get_hostname(void)
{
	int		fd;
	char	*temp;
	char	*rest;
	char	*hostname;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (NULL);
	temp = get_next_line(fd);
	rest = get_next_line(fd);
	while (rest != NULL)
	{
		free(rest);
		rest = get_next_line(fd);
	}
	if (temp != NULL)
	{
		fd = 0;
		while (temp[fd] != '.')
			fd++;
		hostname = ft_substr(temp, 0, fd);
		free(temp);
		if (!hostname)
			return (NULL);
	}
	else
		return (NULL);
	return (hostname);
}
char	*get_cwd(char *home)
{
	char	*temp;
	char	*cwd;

	temp = getcwd(NULL, 0); //motra o ggoncalv no sgoinfre. pegar o pwd em vez do cwd?
	if (temp == NULL)
		return (NULL);
	if (ft_strncmp(temp, home, ft_strlen(home)) == 0)
	{
		if (ft_strlen(temp) > ft_strlen(home))
		{
			cwd = ft_strjoin("~", temp + ft_strlen(home));
		}
		else
			cwd = "~";
		free(temp);
	}
	else
		cwd = temp;
	free(home);
	return (cwd);
}

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
	return (free(user), free(hostname), free(cwd), prompt);
}