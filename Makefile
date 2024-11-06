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
						display/ray_cast.c		display/render.c		action/move.c			action/rotate.c		\
						init/init_data.c		init/init_map.c			init/init_textures.c	init/init_player.c	init/init_colors.c		\
						utils/exit.c			utils/utils_map.c		utils/get_next_line.c	utils/utils_str.c	utils/utils_texture.c	
SRC			= $(addprefix $(SRC_PATH), $(SRC_FILES))

SRC_B_FILES 		=	bonus/cub3d_bonus.c					\
						bonus/action/door_bonus.c			bonus/action/move_bonus.c			bonus/action/rotate_bonus.c		bonus/action/shoot_bonus.c		\
						bonus/display/faces_weapon_bonus.c	bonus/display/floor_bonus.c			bonus/display/minimap_bonus.c	bonus/display/ray_cast_bonus.c	\
						bonus/display/render_bonus.c		bonus/display/sprites_bonus.c		\
						bonus/init/init_bonus.c				bonus/init/init_colors_bonus.c		bonus/init/init_data_bonus.c			bonus/init/init_ennemis_bonus.c	\
						bonus/init/init_map_bonus.c			bonus/init/init_textures_bonus.c	\
						bonus/utils/utils_bonus.c			bonus/utils/utils_sprites_bonus.c	\
						utils/exit.c						utils/utils_map.c					utils/get_next_line.c			utils/utils_str.c				\
						utils/utils_texture.c				display/render.c					init/init_textures.c			init/init_player.c
SRC_B		= $(addprefix $(SRC_PATH), $(SRC_B_FILES))

OBJ_PATH	= obj/

OBJ_FILES	= $(SRC:.c=.o)
OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_FILES))

OBJ_B_FILES	= $(SRC_B:.c=.o)
OBJ_B		= $(addprefix $(OBJ_PATH), $(OBJ_B_FILES))

NAME		= cub3d
NAME_B		= cub3d_bonus

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -I$(INCLUDES_PATH) -I$(MLX_PATH) -I$(LIBFTPRINTF_PATH) -g3

LDFLAGS	= -L$(MLX_PATH) -L$(LIBFTPRINTF_PATH)

LDLIBS	= -lmlx_Linux -lXext -lX11 -lm -lftprintf

BONUS_FLAG	= -D BONUS=1

RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFTPRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFTPRINTF_LIB):
	@make -C $(LIBFTPRINTF_PATH)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(OBJ_PATH)%.o:	%.c
	@mkdir -p ${@D}
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B) $(MLX_LIB) $(LIBFTPRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJ_B) $(LDFLAGS) $(LDLIBS) $(BONUS_FLAG) -o $(NAME_B)

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
