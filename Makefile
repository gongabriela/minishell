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

SRC = free.c env.c debug.c minishell.c prompt.c pre_parsing.c main.c
OBJ = $(SRC:.c=.o)

LIBFT = ./Libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./Libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

debug:
	make -C ./Libft
	$(CC) $(CFLAGS) -g $(SRC) $(LIBFT) -lreadline -o $(NAME)
	gdb --tui $(NAME)


clean:
	make -C ./Libft fclean
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all