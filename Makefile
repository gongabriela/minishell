# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 16:20:18 by adias-do          #+#    #+#              #
#    Updated: 2025/07/03 04:45:52 by adias-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RDLINE = -lreadline
LIBFTDIR = libft
RM = rm -rf
SRCS = srcs/rl_test.c srcs/tokenizer/tokenizer.c srcs/tokenizer/tokenizer_utils.c srcs/tokenizer/free.c #srcs/tokenizer/tokenizer_utils2.c #srcs/tokenizer/parse.c
OBJS = $(SRCS:.c=.o)

INCLUDE = -L ./libft -lft

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@make -s -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE) $(RDLINE)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	@make -s -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -s -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re