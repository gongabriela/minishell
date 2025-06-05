/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:55:20 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/03 11:55:20 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_shell shell)
{
	char	*prompt;

	prompt = create_prompt(shell.env);
	printf("prompt: %s\n", prompt);
	free(prompt);
	//shell.input = ft_readline(shell);
}

char	*create_prompt(t_env *env)
{
	char	*logname;
	char	*name;
	char	*home;
	char	*cwd;

	while (env != NULL)
	{
		if (ft_strncmp(env->key, "LOGNAME", 7) == 0)
			logname = ft_strdup(env->content);
		if (ft_strncmp(env->key, "NAME", 4) == 0)
			name = ft_strdup(env->content);
		if (ft_strncmp(env->key, "HOME", 4) == 0)
			home = ft_strdup(env->content);
		env = env->next;
	}
	if (!logname || !name || !home)
		return (NULL);
	cwd = get_cwd(home);
	if (!cwd)
		return (NULL);
	return (get_full_prompt(logname, name, cwd));
}

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

char	*get_full_prompt(char *logname, char *name, char *cwd)
{
	char	*prompt;
	size_t	len;

	len = ft_strlen(logname) + ft_strlen(name) + ft_strlen(cwd) + 5;
	prompt = ft_calloc(len, sizeof(char));
	if (!prompt)
		return (NULL);
	ft_strlcat(prompt, logname, len);
	ft_strlcat(prompt, "@", len);
	ft_strlcat(prompt, name, len);
	ft_strlcat(prompt, ":", len);
	ft_strlcat(prompt, cwd, len);
	ft_strlcat(prompt, "$ ", len);
	return (free(logname), free(name), free(cwd), prompt);
}
