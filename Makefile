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
SRC_FILES 			=	cub3d.c					display/ray_cast.c		display/render.c		\
						utils/utils_debug.c		utils/exit.c			utils/utils_map.c		\
						utils/get_next_line.c	utils/utils_str.c		utils/utils_texture.c	\
						init/init_data.c		init/init_map.c			init/init_textures.c	\
						init/init_colors.c		move/move.c				move/rotate.c

SRC			= $(addprefix $(SRC_PATH), $(SRC_FILES))

OBJ_PATH	= obj/
OBJ			= $(addprefix $(OBJS_PATH), $(SRC))
# OBJ			= $(SRC:.c=.o)

NAME	= cub3d

NAME_B	= cub3d_bonus

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -I$(INCLUDES_PATH) -I$(MLX_PATH) -I$(LIBFTPRINTF_PATH) -g3

LDFLAGS	= -L$(MLX_PATH) -L$(LIBFTPRINTF_PATH)

LDLIBS	= -lmlx_Linux -lXext -lX11 -lm -lftprintf

RM		= rm -f

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFTPRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

# %.o: %.c $(INCLUDES) $(INCLUDES_B)
# 	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(LIBFTPRINTF_LIB):
	@make -C $(LIBFTPRINTF_PATH)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(OBJS_PATH) %.o: %.c $(INCLUDES) $(INCLUDES_B)
	@mkdir -p ${@D}
	@$(CC) $(CFLAGS) -c $< -o $@

bonus : $(NAME_B)

$(NAME_B): $(OBJ_B) $(MLX_LIB) $(LIBFTPRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJ_B) $(LDFLAGS) $(LDLIBS) -o $(NAME_B)

clean:
	$(RM) $(OBJS_PATH)
	@make clean -C $(LIBFTPRINTF_PATH)
	@make clean -C $(MLX_PATH)

fclean: clean
	$(RM) $(NAME) $(NAME_B)
	@make fclean -C $(LIBFTPRINTF_PATH)

re: fclean
	make all

.PHONY: all clean fclean re libft_printf bonus
