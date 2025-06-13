/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:46:28 by adias-do          #+#    #+#             */
/*   Updated: 2025/06/13 16:43:15 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	CMD,		// commands, args and strings
	PIPE,		// |
	REDIR_IN,	// <
	REDIR_OUT,	// >
	APPEND,		// >>
	HEREDOC		// <<
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// tokenizer
t_token	*tokenize(char *input);

// tokenizer_utils
int		is_operator(char c);
t_token	*handle_word(char *input, int *i);
t_token	*handle_operator(char *input, int *i);
t_token	*create_token(char *content, t_token_type type);
void	add_token_to_list(t_token **head, t_token **curr, t_token *new_token);

#endif