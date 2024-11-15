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

# include "../libft_printf/includes/ft_printf.h"
# include "../mlx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//	Defines

# define GAME_NAME "CUB3D"

# define GAME_NAME_B "CS3"

# define ERR_NB_ARG "Error\nOnly 2 parameters required : ./cub3d map.cub"

# define ERR_LINE_FMT "Error\n\
Textures or colors lines couldn't beggin with space"
# define ERR_LINE_COLOR_FMT "Error\n\
Color line format should be F/C 0-255.0-255.0-255"
# define ERR_LINE_TEXTURE_FMT "Error\n\
Texture line format should be XX ./path_to_the_xxxx_texture"

# define ERR_TEXTURES_LOAD_E "Error\nLoading east texture failed"
# define ERR_TEXTURES_LOAD_N "Error\nnLoading north texture failed"
# define ERR_TEXTURES_LOAD_W "Error\nLoading west texture failed"
# define ERR_TEXTURES_LOAD_S "Error\nLoading south texture failed"
# define ERR_TEXTURE_DOUBLE "Error\nSame texture defined multiple times"

# define ERR_COLOR_FMT "Error\nColor format should be 0-255.0-255.0-255"
# define ERR_COLOR_CHA "Error\nNon-numeric character in color"
# define ERR_COLOR_VAL "Error\nColor values should be between 0 and 255"

# define ERR_MAP_EXT "Error\nWrong map extension, you map should be .cub format"
# define ERR_MAP_OPEN "Error\nCouldn't open the map file"
# define ERR_MAP_READ "Error\nCouldn't read the map file"
# define ERR_MAP_LOAD "Error\nCouldn't load the map"
# define ERR_MAP_PLAYER "Error\nYou need exactly 1 player position (N/S/E/W)"
# define ERR_MAP_CHAR "Error\nUnknown character in your map !"
# define ERR_MAP_NL "Error\nEmpry line inside your map"
# define ERR_MAP_OPEN_WALL "Error\nThe map isn't closed"
# define ERR_MAP_OPEN_INSIDE "Error\nThe map is open inside"

# define ERR_ENE_COUNT "Error\nToo many ennemis, maximum 5"
# define ERR_ENE_LOAD "Error\nLoading enemy texture failed"

# define SKY_PATH "./textures/sky.xpm"
# define TERRO_PATH "./textures/terro.xpm"
# define TERRO_D_PATH "./textures/terro_dead.xpm"
# define CT_PATH "./textures/ct.xpm"
# define FAR_PATH "./textures/far.xpm"
# define CLOSE_PATH "./textures/close.xpm"
# define DEAD_PATH "./textures/dead.xpm"
# define DOOR_PATH "./textures/closed_door256.xpm"
# define WEAPON_PATH "./textures/weapon.xpm"
# define SHOOT_PATH "./textures/shoot.xpm"
# define FLOOR_PATH "./textures/floor_tex.xpm"

# define SCR_WIDTH 1920
# define SCR_HEIGHT 1080

# define FACE_SIZE 54
# define TILE_SIZE 20
# define BEN_HEIGHT 256
# define BEN_WIDTH 256

// Azerty
// # define W 122 //Z
// # define S 115
// # define D 100
// # define A 113 //Q

// Qwerty
# define W 119
# define S 115
# define D 100
# define A 97

# define E 101 //E
# define LEFT_CLICK 1

# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define PI 3.141592
# define SPEED 0.1
# define RSPEED 0.02

# define RED_PIXEL 0xFF0000
# define ORA_PIXEL 0xFF5733
# define YEL_PIXEL 0xF0FF33
# define GRE_PIXEL 0x33FF33
# define GRI_PIXEL 0x969696
# define DBL_PIXEL 0x3338FF
# define PUR_PIXEL 0xCF33FF
# define WHI_PIXEL 0xFFFFFF
# define BLA_PIXEL 0x000000
# define NOT_PIXEL 0xff0000

//	Structures

typedef struct s_map
{
	int			fd;
	size_t		width;
	size_t		height;
	char		**map2d;
	char		**map2d_copy;
	char		**minimap;
}				t_map;

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_txr
{
	int			*north;
	int			*south;
	int			*east;
	int			*west;
	int			floor;
	int			ceiling;
	int			color;
	int			height;
	int			width;
	int			*floor_txr;
	int			*door;
	int			bonus_height;
	int			bonus_width;
	int			*sky;
	int			*weapon;
	int			*shoot;
	int			sky_height;
	int			sky_width;
	int			*terro;
	int			*terro_dead;
	int			*ct;
	int			face_height;
	int			face_width;
	int			*far;
	int			*close;
	int			*dead;
	int			ben_height;
	int			ben_width;
}				t_txr;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
}				t_player;

typedef struct s_enemy
{
	int			id;
	double		x;
	double		y;
	int			alive;
	double		distance;
}				t_enemy;

typedef struct s_sprites
{
	double		x;
	double		y;
}				t_sprites;

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
	double		step;
	double		z_buffer[SCR_WIDTH];
	int			*txr;
}				t_ray;

typedef struct s_floor
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;
	int			pos;
	double		pos_z;
	double		ray_dir_x0;
	double		ray_dir_y0;
	double		ray_dir_x1;
	double		ray_dir_y1;
	double		row_distance;
	double		step_x;
	double		step_y;
	double		floor_x;
	double		floor_y;
	double		cell_x;
	double		cell_y;
}				t_floor;

typedef struct s_sprite
{
	double		x;
	double		y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			screen_x;
	int			height;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_y;
	int			width;
	int			draw_start_x;
	int			draw_end_x;
	int			stripe;
	double		distance[5];
}				t_sprite;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_txr		*txr;
	t_map		*map;
	t_player	player;
	t_enemy		ennemis[5];
	int			ennemis_count;
}				t_data;

//	Enum

//	Fonctions

// Initialisation
int				init_data(t_data *data, char *map_path);

// Textures
char			*get_texture_path(char *line);
int				init_textures(char *map_path, t_data *data);
int				check_line(char *line, int i, t_txr *txr);
int				check_textures(t_txr *txr, int map_fd);
int				set_color(char *line);

// Map
char			*load_map(t_data *data);
int				init_map(t_data *data);
int				check_space_inside(char **map2d);
void			find_player(t_data *data);

// Affichage
int				ray_cast(t_data *data);
int				ray_cast_b(t_data *data);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			load_col_txr(t_ray *ray, t_data *data);
void			load_col_txr_b(t_ray *ray, t_data *data);

// Deplacements
int				handle_key(int key_code, t_data *data);
void			rotate_right(t_player *player);
void			rotate_left(t_player *player);

// Bonus

// Init
int				init_data_b(t_data *data, char *map_path);
int				control_char_map_bonus(char *map1d);
int				init_bonus(t_data *data);
int				init_ennemis(t_data *data);
int				control_char_map_bonus(char *map1d);
int				door(t_player *player, t_data *data);

// Textures
int				init_textures_bonus(t_data *data);
int				*bonus_xpm_to_img(t_data *data, char *path);

// Actions
int				mouse_move(int x, int y, t_data *data);
int				mouse_click(int key_code, int x, int y, void *data);
int				shoot(t_player *player, double x, double y, t_data *data);

// Prints
void			load_floor(t_data *data);
void			print_minimap(t_data *data);
void			print_faces(t_data *data);
void			print_sprites(t_data *data, t_ray ray, t_player player);
void			print_weapon(t_data *data, int *txr);

// Utils
char			*get_next_line(int fd);
void			close_gnl(int fd);
char			*ft_join(char *s1, char *s2, int nb_read);
int				skip_char(char *str, char to_skip);
char			*crea_row(char c, int size);
char			*ft_strndup(char *str, t_data *data);
void			sort_sprites(double *distances, t_enemy *ennemis,
					int sprites_count);

// Free/Exit
int				exit_pgm(t_data *data, int exit_code);
void			free_data(t_data *data);

#endif
