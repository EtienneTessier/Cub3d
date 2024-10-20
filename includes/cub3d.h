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
# define ERR_TEXTURES_LOAD "Error when loading a sprite"
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
# define TXR_SIZE 64
# define TILE_SIZE 25
// Azerty
# define W 122
# define S 115
# define D 100
# define A 113
// Qwerty
// # define W 119
// # define S 115
// # define D 100
// # define A 97
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
	int			*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_txtr
{
	int			*north;
	int			*south;
	int			*east;
	int			*west;
	int			*floor;
	int			*ceiling;
	int			color;
	int			height;
	int			width;
}				t_txr;

typedef struct	s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
}				t_player;

typedef struct s_ray
{
	int			x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		camera_x;
	int			map_x;
	int			map_y;
	double		side_distx;
	double		side_disty;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	double		tex_pos;
	int			tex_x;
	int			tex_y;
	int			step;
	int			*txr;
}				t_ray;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_txr		*txtr;
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
int		ray_cast(t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	load_col(t_ray *ray, t_data *data);
void	load_col_txr(t_ray *ray, t_data *data);

// Deplacements
int		handle_key(int key_code, t_data *data);

// Utils
char	*get_next_line(int fd);
char	*ft_join(char *s1, char *s2, int nb_read);
int		skip_char(char *str, char to_skip);

// Free/Exit
void	free_data(t_data *data);
int		exit_pgm(t_data *data);

// Debug
void	print_map_2d(char **map2d);
int		load_map_img(t_data *data);
void	load_color(t_ray *ray, t_data *data);

#endif
