# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acauchy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 10:04:49 by acauchy           #+#    #+#              #
#    Updated: 2018/09/18 17:19:38 by cpaquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re LIBFT

NAME = fdf

CC =		gcc
CFLAGS =	-Wall -Wextra
CPPFLAG =	-I./includes

SRC_PATH = 	src
SRC_NAME =	main.c \
			get_data.c \
			tools.c \
			isometric.c \
			rotate.c \
			key_effect.c \
			draw_line.c

OBJ_PATH =	objs
OBJ_NAME =	$(SRC_NAME:.c=.o)
OBJ =		$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFT_PATH =	libraries

FLAGS_MINILIBX = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): LIBFT $(OBJ)
	@ $(CC) $(OBJ) $(CPPFLAG) -L$(LIBFT_PATH) -lft $(FLAGS_MINILIBX) -o $(NAME)
	@ echo "\x1B[032m" "-= $(NAME) OK =-" "\x1B[0m"

LIBFT:
	@ make -C $(LIBFT_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@ mkdir -p $(OBJ_PATH)
	@ $(CC) -c $(CFLAGS) $(CPPFLAG) $^ -o $@

clean:
	@ rm -Rf $(OBJ_PATH)
	@ make -C $(LIBFT_PATH) clean
	@ echo "\x1B[031m" "-= Objs deleted" "\x1B[0m"

fclean: clean
	@ make -C $(LIBFT_PATH) fclean
	@ rm -f $(NAME)
	@ echo "\x1B[031m" "-= $(NAME) deleted =-" "\x1B[0m"

re: fclean all
