/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:46:28 by adias-do          #+#    #+#             */
/*   Updated: 2025/07/03 04:49:28 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

// commands, args and strings (delete)
// |
// <
// >
// >>
// << (delete)
typedef enum e_token_type
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	int				len;	/* tamanho original (delete) */
	bool			to_del;	/* o que deve ser deletado depois (ex: aspas) (delete) */
	struct s_token	*next;
}	t_token;

typedef struct s_token_oprt
{
	int				len;
	char			*token;
	t_token_type	type;
}	t_token_oprt;

// tokenizer
t_token			*tokenize(char *input);
/*int		validate_token(t_token *tokens);*/

// tokenizer_utils
int				is_operator(char c);
/*int		is_incomplete_input(t_token *tokens);*/
void			free_tokens(t_token *head);
void			add_token(t_token **list, t_token *new_token);
void			add_token_and_free(t_token **list, t_token *token, t_token_oprt *oprt);
char			update_quote_state(char quote_state, char curr_char);
t_token			*handle_word(char *input, int *i);
t_token			*create_token(char *str, t_token_type type, int len);
t_token_oprt	handle_operator(char *input);

#endif