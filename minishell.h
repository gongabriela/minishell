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
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

//estrutura principal--------------------------------------------
typedef struct s_shell
{
	struct s_env	*env;
	char			**cmd_paths;
	char			*prompt;
	char			*input;

}					t_shell;

//estrutura para as variaveis de ambiente-------------------------
typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}						t_env;


// --------- Funções principais -------------------------------

void	check_args(int argc, char **argv, char **envp);
void	init_structs(t_shell *shell);
void	minishell(t_shell *shell, char **envp);

// --------- Funções auxiliares para pegar as env --------------

void	get_env(t_shell *shell, char **envp);
void	get_cmd_paths(t_shell *shell, char *path_str);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
t_env	*create_env_node(char *env, t_shell *shell);

// ------------- Funcoes de criar o prompt --------------------

char	*create_prompt(t_env *env);
char	*get_cwd(char *home);
char	*get_full_prompt(char *logname, char *name, char *cwd);
char	*get_hostname(void);
char	*get_hostname_line(int fd);

// --------- Funções de free -----------------------------------

void	free_cmd_paths(char **cmd);
void	free_struct_env(t_env *env);
void	ft_free_shell(t_shell *shell);
void	ft_error(char *msg, t_shell *shell);

// --------- Funcoes de debug ----------------------------------

void	print_env_list(t_env *env);
void	print_cmd_paths(char **paths);

#endif