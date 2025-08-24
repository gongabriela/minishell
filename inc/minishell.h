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
# include "../libft/libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>

//estrutura principal--------------------------------------------
typedef struct s_shell
{
	struct s_env	*env;
	struct s_token	*tokens;
	struct s_exec	*tree;
	char			*prompt;
	char			*input;
	char			*pwd;
	int				exit_code;
	char			**envp;
	int				**pipe_fds;
	int				cmd_total;
	int				pid_index;
	pid_t			*pids;
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

// commands, args and strings (delete)
// |
// <
// >
// >>
// <<
typedef enum e_token_type
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	FILENAME,
	DELIMITER
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	int				len;
	int				was_variable;
	bool			to_del;
	struct s_token	*next;
}	t_token;

typedef struct s_token_oprt
{
	int				len;
	char			*token;
	t_token_type	type;
}	t_oprt;

// estrutura temporaria para AST -----------------------------
typedef struct s_exec
{
	char				**cmd;
	char				*oprt;
	char				*filename;
	char				*delimiter;
	t_token_type		type;
	struct s_exec		*left;
	struct s_exec		*right;
	int					stdin;
	bool				in_file;
	int					stdout;
	bool				out_file;
	bool				created_out;
	struct s_hdc		*heredoc;
}	t_exec;

typedef struct s_hdc
{
	char	*file_name;
	int		fd;
}	t_hdc;

// --------- Funções principais -------------------------------

void	check_args(int argc, char **argv, char **envp);
void	init_structs(t_shell *shell);
void	minishell(t_shell *shell);

// --------- Funções auxiliares para pegar as env --------------

void	get_env(t_shell *shell, char **envp);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
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

// --------------- Main tokenizer ------------------------
t_token	*tokenize(char *input);

// ---------- tokenizer utilities ----------------------

// operator checks
int		is_operator(char c);

// token list manipulation
void	add_token(t_token **list, t_token *new_token);
void	add_token_and_free(t_token **list, t_token *token, t_oprt *oprt);

// quote state handling
char	update_quote_state(char quote_state, char curr_char);

// token creation and handling
t_token	*handle_word(char *input, int *i);
t_token	*create_token(char *str, t_token_type type, int len);
t_oprt	handle_operator(char *input);

// --------- Variable expansion and token expansion ------------

// variable validation
int		is_valid_var_char(char c);
int		is_valid_var_start(char c);

// variable expansion
void	expand_tokens(t_shell *sh);
char	*ft_expander(t_shell *sh, char *token);
char	*expand_var(t_shell *shell, char *token);
char	*ft_get_var(t_env *env, const char *key);

// dolar, quotes and tilde
char	*expand_dollar(t_shell *shell, char *str, int *i);
char	*expand_single_quotes(char *str, int *i);
char	*expand_double_quotes(t_shell *shell, char *str, int *i);
char	*expand_tilde(t_shell *shell, char *token, int *i);

// helper functions
void	add_str_to_list(t_list **list, void *content);
char	*ft_join_list_and_free(t_list **lst, char sep);
char	*ft_strjoin_free(char *s1, char *s2, int free_flag);

// --------- Funções de free -----------------------------------

void	free_struct_env(t_env *env);
void	ft_free_shell(t_shell *shell);
void	ft_exit(t_shell *shell, int exit_code);
void	free_struct_tokens(t_token *tokens);
void	free_cmd_and_args(char **cmd);

// --------- Funcoes de debug ----------------------------------

void	print_cmd_paths(char **paths);

// --------- Funcoes de builtins -------------------------------

// --------- Builtin: echo ----------------------------------
void	echo(t_shell *shell, char **args);
int		check_n_flags(int *n_flag, char **args);

// --------- Builtin: pwd -----------------------------------
void	pwd(t_shell *shell);

// --------- Builtin: env -----------------------------------
void	env(t_shell *shell, char **cmd);
void	print_env_list(t_env *env);

// --------- Builtin: exit ----------------------------------
void	ft_exit_builtin(t_shell *shell, char **args);
int		check_exit_args(t_shell *shell, char **args);
void	get_exit_code(t_shell *shell, char **args);

// --------- Builtin: cd ------------------------------------
char	*get_env_value_cd(t_env *env, const char *key);
void	cd_error(char *msg, char *arg, t_shell *shell, int exit_code);
int		cd_too_many_args(char **args);
char	*cd_get_path(char **args, char *home, char *oldpwd);
void	update_pwd_env(t_shell *shell, char *oldpwd);
void	cd(t_shell *shell, char **args);

// --------- Builtin: unset ---------------------------------
void	unset(t_shell *shell, char **args);
int		check_invalid_option(char **args);

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

// --------- Funções da AST -----------------------------------
int		create_ast(t_shell *shell, t_token *tokens);
t_exec	*create_node_ast(t_token **tokens, t_shell *shell);
void	add_node_ast(t_exec *node, t_exec **root);
void	ft_free_ast(t_exec *tree);
char	**get_cmd_and_args(t_token **tokens, t_shell *shell);
char	**get_full_cmd(t_token **tokens);
char	**get_simple_cmd(t_token **tokens);
void	print_ast(t_exec *node, int level);

void	init_node(t_exec *node, t_token **tokens);
int		create_node_pipe(t_exec *node, t_token **tokens, t_shell *shell);
int		create_node_redir(t_exec *node, t_token **tokens, t_shell *shell);
int		create_node_cmd(t_exec *node, t_token **tokens, t_shell *shell);
void	ft_free_node(t_exec *node);

// --------- Funções de execução ------------------------------
void	execute_builtin(t_shell *shell, t_exec *tree, char **cmd);
void	execution(t_exec *tree, t_shell *shell, int *pid_index);
int		is_builtin(char **cmd);

void	execute_external_cmd(t_exec *tree, t_shell *shell, int pid_index);
void	check_invalid_fds(t_exec *tree, t_shell *shell);
void	redir_io(t_exec *tree, t_shell *shell);
void	close_unused_pipes(t_exec *tree, t_shell *shell);
char	*get_cmd_path(char **cmd, t_shell *shell);
char	*find_exec_path(char **split_paths, char *cmd);
int		check_for_slash(char *cmd, t_shell *shell);
void	get_envp(t_shell *shell);
void	copy_envp_values(char **envp, t_env *env);
void	free_envp_array(char **envp);
void	ft_free_split(char **split);

void	error_msg(char *msg, char *cmd, char *arg);

void	pre_execution(t_exec *tree, t_shell *shell);
int		get_cmd_total(t_token *head);
int		**init_pipes(t_shell *shell);
int		create_pipes(t_shell *shell, t_exec *tree, int **pipe_fds, int i);
void	ft_free_pipes(int **pipe_fds, int cmd_total);

void	exec_cmd(t_exec *tree, t_shell *shell, int index);
void	exec_cmd_child(t_exec *tree, t_shell *shell);
void	wait_pids(t_shell *shell);
void	close_all_pipes(t_shell *shell);

void	handle_infile(t_exec *tree, char *file);
void	handle_outfile(t_exec *tree, char *file);
void	handle_append(t_exec *tree, char *file);

void	execute_redirs(t_exec *tree, int **pipe_fds, int *i);
void	handle_pipe(t_exec *tree, int **pipe_fds, int *i);

void	handle_heredoc(t_exec *tree);
void	execute_heredocs(t_exec *tree, t_shell *shell);
void	process_heredoc(t_exec *tree, t_shell *shell, t_hdc *heredoc);
void	heredoc_child_process(t_exec *tree, t_shell *shell, t_hdc *heredoc);
char	*heredoc_alloc_name(t_shell *shell, char *temp, int i);
char	*get_random_name(t_shell *shell);
void	get_heredoc_input(t_shell *shell, t_exec *tree, t_hdc *heredoc);
void	free_heredoc_struct(t_hdc *heredoc);

//signals
void	handle_sigint(int sig);
void	setup_signals_prompt(void);
void	handle_signals_child(void);
void	handle_signals_shell(void);

void	free_exit_child(t_shell *shell, int exit_code);

void	error_msg_redir(t_exec *tree, int err_code, char *file, int std);
void	close_opened_fds(t_exec *tree, int std);
void	close_all_fds(t_exec *tree);
void	unlink_heredocs(t_exec *tree);
#endif