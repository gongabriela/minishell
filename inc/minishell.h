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
# include "../Libft/libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>

//estrutura principal--------------------------------------------
typedef struct s_shell
{
	struct s_env	*env;
	char			*prompt;
	char			*input;
	char			*pwd;
	int				exit_code;
	char			**envp;

}					t_shell;

//estrutura para as variaveis de ambiente-------------------------
typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
	bool			export;
	bool			env;
}						t_env;

// --------- Funções principais -------------------------------

void	check_args(int argc, char **argv, char **envp);
void	init_structs(t_shell *shell);
void	minishell(t_shell *shell);

// --------- Funções auxiliares para pegar as env --------------

void	get_env(t_shell *shell, char **envp);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
t_env	*create_env_node(char *env, t_shell *shell);

// ------------- Funcoes de criar o prompt --------------------

char	*create_prompt(t_shell *shell);
char	*get_env_value(t_env *env, const char *key);
char	*get_cwd(t_env *env, char *pwd);
char	*get_full_prompt(char *logname, char *name, char *cwd);
char	*get_hostname(void);
char	*get_hostname_line(int fd);
int		pre_parsing(char *input);
int		get_input(t_shell *shell);

// --------- Funções de free -----------------------------------

void	free_struct_env(t_env *env);
void	ft_free_shell(t_shell *shell);
void	ft_exit(t_shell *shell, int exit_code);

// --------- Funcoes de debug ----------------------------------

void	print_cmd_paths(char **paths);

// --------- Funcoes de builtins -------------------------------

// --------- Builtin: echo ----------------------------------
void	echo(t_shell *shell, char **args);
int		check_n_flags(int *n_flag, char **args);

// --------- Builtin: pwd -----------------------------------
void	pwd(t_shell *shell);

// --------- Builtin: env -----------------------------------
void	env(t_shell *shell);
void	print_env_list(t_env *env);

// --------- Builtin: exit ----------------------------------
void	ft_exit_builtin(t_shell *shell, char **args);
void	check_exit_args(t_shell *shell, char **args);
void	get_exit_code(t_shell *shell, char **args);

// --------- Builtin: cd ------------------------------------
void	cd(t_shell *shell, char **args);

// --------- Builtin: unset ---------------------------------
void	unset(t_shell *shell, char **args);

// --------- Builtin: export --------------------------------
int		parse_export_args(t_shell *shell, char *arg);
t_env	*search_var_in_env(t_shell *shell, char *arg);
void	update_env_var(t_shell *shell, t_env *var, char *arg);
void	insert_env_sorted(t_shell *shell, t_env *new);
void	create_new_env_var(t_shell *shell, char *arg);
void	export(t_shell *shell, char **args);

t_env	*copy_env_node(t_env *src);
void	insert_sorted(t_env **sorted, t_env *node);
void	print_sorted_env(t_env *sorted);
void	free_env_list(t_env *lst);
void	print_export_table(t_shell *shell);

// --------- Builtin: argument parsing/testing ---------------
int		skip_spaces(const char *s);
int		skip_quotes(const char *s, char quote);
int		arg_len(const char *s);
int		count_args(const char *s);
char	*copy_arg(const char *s, int len);
char	*extract_arg(const char **s);
char	**split_args(const char *s);

#endif