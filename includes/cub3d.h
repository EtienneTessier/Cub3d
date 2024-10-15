/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:42:27 by etessier          #+#    #+#             */
/*   Updated: 2024/10/09 11:55:30 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//	Includes

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft_printf/includes/ft_printf.h"
# include "../libft_printf/libft/include/libft.h"
# include "../mlx-linux/mlx.h"

//	Defines

# define ERR_NB_ARG "Only 2 parameters required : ./cub3d maps.cub"
# define ERR_MAP_EXT "Wrong map extension"
# define ERR_MAP_PLAYER "You need exactly 1 player position (N/S/E/W)"
# define ERR_MAP_OPEN "Map open error"
# define ERR_MAP_OPEN_WALL "The map isn't closed"
# define ERR_TEXTURES "Wrong textures"
# define ERR_TEXTURE_FMT "Wrong texture format"
# define ERR_TEXTURE_DOUBLE "Same texture defined multiple times"
# define ERR_XPM "Textures need to be xpm files"
# define ERR_COLOR "Color format should be 0.0-255.0-255"
# define ERR_MAP_NL "Empry line inside your map"
# define ERR_CHAR_MAP "Unknown character in your map !"
# define COLOR 0
# define TEXTURE 1
# define SCR_WIDTH 720
# define SCR_HEIGHT 480
# define TILE_SIZE 25
# define W 119
# define S 115
# define D 100
# define A 97
# define ESC 65307
# define PI 3.141592
# define SPEED 0.1
# define RSPEED 0.1

# define RED_PIXEL 0xFF0000
# define ORA_PIXEL 0xFF5733
# define YEL_PIXEL 0xF0FF33
# define GRE_PIXEL 0x33FF33
# define GRI_PIXEL 0x969696
# define DBL_PIXEL 0x3338FF
# define PUR_PIXEL 0xCF33FF
# define WHI_PIXEL 0xFFFFFF
# define BLA_PIXEL 0x000000

//	Structures

typedef struct	s_txtr
{
	void		*north;
	void		*south;
	void		*east;
	void		*west;
	int			*floor;
	int			*ceiling;
	int			height;
	int			width;
}				t_txtr;

typedef struct	s_map
{
	int			fd;
	size_t		width;
	size_t		height;
	char		**map2d;
	char		**map2d_copy;
}				t_map;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_player
{
	int			x;
	int			y;
	double		dir;
	double		dir_x;
	double		dir_y;
}				t_player;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_txtr		*txtr;
	t_map		*map;
	t_player	player;
}				t_data;

//	Enum

typedef enum	e_error
{
	NB_ARG	,
	MAP_EXT
}				t_error;

//	Fonctions

// Initialisation
t_data	*init_data(char *map_path);

int		init_textures(char *map_path, t_data *data);

int		init_map(t_data *data);
char	*load_map(t_data *data);
void	find_player(t_data *data);

// Affichage
void	load_img(t_img *img);
int		load_map_img(t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// Deplacements
int		handle_key(int key_code, t_data *data);
void	get_player_dir(char c, t_data *data);

// Utils
char	*get_next_line(int fd);
char	*ft_join(char *s1, char *s2, int nb_read);
int		skip_char(char *str, char to_skip);

// Free/Exit
void	free_data(t_data *data);
int		exit_pgm(t_data *data);

// Debug
void	print_map_2d(char **map2d);

#endif
