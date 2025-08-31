/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   714_exec_heredoc_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 05:45:55 by adias-do          #+#    #+#             */
/*   Updated: 2025/08/31 19:09:44 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	handle_eof_warning(int line_number, char *delimiter)
{
	fprintf(stderr, "bash: warning: here-document at line %d delimited by "
		"end-of-file (wanted `%s')\n", line_number, delimiter);
}

static void	write_line_to_heredoc(t_hdc *heredoc, char *input,
								t_shell *shell, bool should_expand)
{
	char	*expanded_input;

	if (should_expand)
	{
		expanded_input = ft_expander(shell, input);
		write(heredoc->fd, expanded_input, ft_strlen(expanded_input));
		free(expanded_input);
	}
	else
		write(heredoc->fd, input, ft_strlen(input));
	write(heredoc->fd, "\n", 1);
}

static bool	delimiter_is_quoted(char *delimiter)
{
	int		i;
	char	quote_state;
	bool	has_quotes;

	i = 0;
	quote_state = 0;
	has_quotes = false;
	if (!delimiter)
		return (false);
	while (delimiter[i])
	{
		if (delimiter[i] == '"' || delimiter[i] == '\'')
			has_quotes = true;
		quote_state = update_quote_state(quote_state, delimiter[i]);
		i++;
	}
	return (has_quotes && quote_state == 0);
}

/**
 * @brief Reads user input for a heredoc and writes it to the heredoc file.
 *
 * Continues reading lines until the delimiter is encountered.
 * @param tree Pointer to the AST node containing the delimiter.
 * @param heredoc Pointer to the heredoc structure with the file descriptor.
 */
void	get_heredoc_input(t_exec *tree, t_hdc *heredoc, t_shell *shell)
{
	char	*input;
	int		line_number;
	bool	should_expand;

	line_number = 1;
	should_expand = !delimiter_is_quoted(tree->right->delimiter);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			handle_eof_warning(line_number, tree->right->delimiter);
			break ;
		}
		if (!ft_strncmp(input, tree->right->delimiter,
				ft_strlen(tree->right->delimiter)))
		{
			free(input);
			break ;
		}
		write_line_to_heredoc(heredoc, input, shell, should_expand);
		free(input);
		line_number++;
	}
}
