# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:14:05 by lsadikaj          #+#    #+#              #
#    Updated: 2024/12/11 14:35:24 by lsadikaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes -I libft -I bonus

SRC = src/main.c src/pipex.c
SRC_BONUS = bonus/main_bonus.c bonus/pipex_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make -C libft fclean

re: fclean all