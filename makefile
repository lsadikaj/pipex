# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:14:05 by lsadikaj          #+#    #+#              #
#    Updated: 2024/12/26 12:04:05 by lsadikaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes -I libft -I bonus

SRC = src/pipex.c src/utils.c
SRC_BONUS = bonus/pipex_bonus.c bonus/utils_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L libft -lft

bonus: $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) -L libft -lft

$(OBJ_BONUS): $(SRC_BONUS)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make -C libft fclean

re: fclean all
