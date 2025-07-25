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

SRC =	./src/tokenizer/rl_test.c ./src/tokenizer/tokenizer.c \
		./src/tokenizer/tokenizer_utils.c \
		./src/free.c ./src/get_env.c ./src/minishell.c \
		./src/prompt/prompt.c ./src/prompt/prompt_utils.c \
		./src/pre_parsing.c ./src/builtins/builtin_testing.c ./src/builtins/echo.c \
		./src/builtins/env.c ./src/builtins/pwd.c ./src/builtins/exit.c \
		./src/builtins/cd/cd.c ./src/builtins/cd/cd_utils.c ./src/builtins/unset.c \
		./src/builtins/export/export.c \
		./src/builtins/export/export_utils.c ./src/builtins/export/export_utils_2.c ./src/main.c
OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

debug:
	make -C ./Libft
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
