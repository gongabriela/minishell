# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/02 10:06:08 by ggoncalv          #+#    #+#              #
#    Updated: 2025/06/02 10:06:08 by ggoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC =	./src/tokenizer/tokenizer.c \
		./src/tokenizer/tokenizer_utils.c \
		./src/tokenizer/tokenizer_utils_2.c \
		./src/tokenizer/tk_expander.c \
		./src/tokenizer/tk_exp_utils.c \
		./src/tokenizer/tk_exp_join.c \
		./src/tokenizer/tk_exp_quotes.c \
		./src/tokenizer/tk_exp_dolar.c \
		./src/free.c ./src/get_env.c ./src/minishell.c \
		./src/prompt/prompt.c ./src/prompt/prompt_utils.c \
		./src/pre_parsing.c ./src/builtins/echo.c \
		./src/builtins/env.c ./src/builtins/pwd.c ./src/builtins/exit.c \
		./src/builtins/cd/cd.c ./src/builtins/cd/cd_utils.c ./src/builtins/unset.c \
		./src/builtins/export/export.c \
		./src/builtins/export/export_utils.c ./src/builtins/export/export_utils_2.c \
		./src/ast/create_ast.c  ./src/ast/create_node_ast.c ./src/ast/ast_utils.c \
		./src/ast/print_ast.c ./src/execution/exec.c \
		 ./src/execution/exec_builtin.c ./src/execution/exec_external_cmd.c \
		./src/execution/pre_exec.c ./src/execution/exec_redirs.c ./src/main.c \

OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

debug:
	make -C ./libft
	$(CC) $(CFLAGS) -g $(SRC) $(LIBFT) -lreadline -o $(NAME)
	gdb --tui $(NAME)


clean:
	make -C ./libft fclean
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: all
	@chmod +x tests.sh
	@./tests.sh ./minishell
