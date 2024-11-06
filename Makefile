# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 12:48:02 by etessier          #+#    #+#              #
#    Updated: 2024/10/09 12:48:03 by etessier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTPRINTF_PATH	= libft_printf
LIBFTPRINTF_LIB		= $(LIBFTPRINTF_PATH)/libftprintf.a

MLX_PATH			= mlx-linux
MLX_LIB				= $(MLX_PATH)/libmlx_Linux.a

INCLUDES_PATH		= include

INCLUDES_FILES		= cub3d.h
INCLUDES			= $(addprefix $(INCLUDES_PATH), $(INCLUDES_FILES))

SRC_PATH			=	sources/
SRC_FILES 			=	cub3d.c					\
						display/ray_cast.c		display/render.c		display/minimap.c			display/faces_weapon.c	display/sprites.c	display/floor.c	\
						utils/utils_debug.c		utils/exit.c			utils/utils_map.c			utils/utils_bonus.c		\
						utils/get_next_line.c	utils/utils_str.c		utils/utils_texture.c		utils/utils_sprites.c	\
						init/init_data.c		init/init_map.c			init/init_textures.c		init/init_player.c		\
						init/init_colors.c		init/init_bonus.c		init/init_textures_bonus.c	init/init_ennemis.c		\
						action/move.c			action/rotate.c			action/shoot.c				action/door.c

SRC			= $(addprefix $(SRC_PATH), $(SRC_FILES))

OBJ_PATH	= obj/
OBJ_FILES	= $(SRC:.c=.o)
OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_FILES))

NAME		= cub3d

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -I$(INCLUDES_PATH) -I$(MLX_PATH) -I$(LIBFTPRINTF_PATH) -g3

LDFLAGS	= -L$(MLX_PATH) -L$(LIBFTPRINTF_PATH)

BONUSFLAGS	= -D BONUS=1

LDLIBS	= -lmlx_Linux -lXext -lX11 -lm -lftprintf

RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFTPRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS) $(BONUSFLAGS) -o $(NAME)

$(LIBFTPRINTF_LIB):
	@make -C $(LIBFTPRINTF_PATH)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(OBJ_PATH)%.o:	%.c
	@mkdir -p ${@D}
	@$(CC) $(CFLAGS) -c $< -o $@

bonus : $(OBJ) $(MLX_LIB) $(LIBFTPRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS) $(BONUSFLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJ_PATH)
	@make clean -C $(LIBFTPRINTF_PATH)
	@make clean -C $(MLX_PATH)

fclean: clean
	@$(RM) $(NAME) $(NAME_B)
	@make fclean -C $(LIBFTPRINTF_PATH)

re: fclean
	@make all

.PHONY: all clean fclean re libft_printf bonus
