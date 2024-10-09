INCLUDESFILES	= ft_printf.h

INCLUDESPATH	= $(DIRPATH)includes/

INCLUDES	= $(addprefix $(INCLUDESPATH), $(INCLUDESFILES))

FILES		= ft_printf.c		trt_num_dec.c		trt_num_hex.c

SRCPATH		= $(DIRPATH)srcs/

SRC		= $(addprefix $(SRCPATH), $(FILES))

LIBFTPATH	= ./libft

OBJ		= $(SRC:.c=.o)

NAME		= libftprintf.a

CC		= cc

CFLAGS		= -Wall -Wextra -Werror

AR		= ar rcs

RM		= rm -f

all: $(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFTPATH)
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			$(AR) $(NAME) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	@make -C $(LIBFTPATH)

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFTPATH)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: all clean fclean re libft
