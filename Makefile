# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/30 14:15:00 by mabdelsa          #+#    #+#              #
#    Updated: 2024/03/30 14:32:40 by mabdelsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= ./cub3D.c

NAME = cub3D
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

LIBFT_P = ./libft/
LIBFT_AR = ./libft/libft.a

MLX_P = ./mlx/
MLX_AR = ./mlx/libmlx.a

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -I $(MLX_P) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR) $(MLX_AR)
	$(CC) $(OBJS) $(MLX_FLAGS) $(MLX_AR) $(LIBFT_AR) -o $(NAME)

$(LIBFT_AR):
	make -C $(LIBFT_P)

$(MLX_AR):
	make -C $(MLX_P)

clean:
	make -C $(MLX_P) clean
	make -C $(LIBFT_P) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_P) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re