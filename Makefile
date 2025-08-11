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


SRC = \
	./src/000_main/010_main.c \
	./src/100_get_env/110_get_env.c \
	./src/1000_free/1100_free.c \
	./src/200_minishell/210_minishell.c \
	./src/300_prompt/310_prompt.c \
	./src/300_prompt/320_prompt_utils.c \
	./src/400_pre_parsing/410_pre_parsing.c \
	./src/500_tokenizer/510_tokenizer.c \
	./src/500_tokenizer/520_tokenizer_utils.c \
	./src/500_tokenizer/530_rl_test.c \
	./src/600_ast/610_create_ast.c \
	./src/600_ast/620_create_node_ast.c \
	./src/600_ast/630_ast_utils.c \
	./src/700_execution/720_exec.c \
	./src/700_execution/730_exec_builtin.c \
	./src/700_execution/740_exec_path.c \
	./src/700_execution/710_pre_exec/711_pre_exec.c \
	./src/700_execution/710_pre_exec/712_exec_heredoc.c \
	./src/700_execution/710_pre_exec/713_exec_heredoc_utils.c \
	./src/700_execution/710_pre_exec/714_create_pipes.c \
	./src/700_execution/710_pre_exec/715_exec_redirs.c \
	./src/700_execution/710_pre_exec/716_exec_redirs_utils.c \
	./src/800_builtins/810_cd.c \
	./src/800_builtins/811_cd_utils.c \
	./src/800_builtins/820_echo.c \
	./src/800_builtins/830_env.c \
	./src/800_builtins/840_exit.c \
	./src/800_builtins/850_export.c \
	./src/800_builtins/851_export_utils.c \
	./src/800_builtins/852_export_utils_2.c \
	./src/800_builtins/860_pwd.c \
	./src/800_builtins/870_unset.c \
	./src/900_signals/910_signals.c \

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
