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
# include "../libft_printf/includes/ft_printf.h"
# include "../libft_printf/libft/include/libft.h"
# include "../mlx-linux/mlx.h"

//	Defines

# define ERR_NB_ARG "Only 2 parameters required : ./cub3d maps.cub"
# define ERR_MAP_EXT "Wrong map extension"
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
# define W 119
# define S 115
# define D 100
# define A 97
# define ESC 65307

//	Structures

typedef struct	s_img
{
	void		*north;
	void		*south;
	void		*east;
	void		*west;
	int			*floor;
	int			*ceiling;
	int			height;
	int			width;
}				t_img;

typedef struct	s_map
{
	int			map_fd;
	size_t		map_width;
	size_t		map_height;
	char		**map2d;
	char		**map2d_copy;
}				t_map;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_map		*map;
	t_pos		*player;
}				t_data;

//	Enum

typedef enum	e_error
{
	NB_ARG	,
	MAP_EXT
}				t_error;

//	Fonctions

t_data	*init_data(char *map_path);

int		init_textures(char *map_path, t_data *data);

int		init_map(t_data *data);
char	*load_map(t_data *data);

// Utils
char	*get_next_line(int fd);
char	*ft_join(char *s1, char *s2, int nb_read);
int		skip_char(char *str, char to_skip);

// Free/Exit
void	free_data(t_data *data);
void	exit_pgm(t_data *data);

// Debug
void	print_map_2d(char **map2d);

#endif
