# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/30 14:15:00 by mabdelsa          #+#    #+#              #
#    Updated: 2024/04/30 15:36:58 by aalkaisi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= ./main_parsing.c

NAME = cub3D
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

LIBFT_P = ./libft/
LIBFT_AR = ./libft/libft.a

MLX_P = ./mlx/
MLX_AR = ./mlx/libmlx.a

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT_AR) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT_AR):
	make -C $(LIBFT_P)

$(MLX_AR):
	make -C $(MLX_P)

clean:
	make -C $(LIBFT_P) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_P) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re