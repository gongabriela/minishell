/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:06:16 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/02 10:06:16 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include "Libft/libft.h"
# include <unistd.h>

//estrutura principal
typedef struct s_shell
{
	struct s_env	*env;
	char			**cmd_paths;
	char			*input;

}					t_shell;

//variaveis de ambiente
typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}						t_env;


// --------- Funções principais ---------

void	check_args(int argc, char **argv, char **envp);
void	init_structs(t_shell *shell);
void	get_env(t_shell *shell, char **envp);
void	get_cmd_paths(t_shell *shell, char *path_str);
void	ft_free_shell(t_shell *shell);

//loop
void	minishell(t_shell shell);
char	*create_prompt(t_env *env);
char	*get_cwd(char *home);
char	*get_full_prompt(char *logname, char *name, char *cwd);

// --------- Funções auxiliares de lista ---------

void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);

// --------- Funções auxiliares ---------

void	ft_free_split(char **arr);

// --------- Funcoes de debug -----------

void	print_env_list(t_env *env);
void	print_cmd_paths(char **paths);

#endif