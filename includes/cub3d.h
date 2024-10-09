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
# define ERR_TEXTURES "Wrong textures"
# define ERR_TEXTURE_FMT "Wrong texture format"
# define ERR_TEXTURE_DOUBLE "Same texture defined multiple times"
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

typedef struct	s_data
{
	int			height;
	int			width;
	int			map_fd;
	t_img		*img;
	char		**map2d;
	void		*mlx;
	void		*win;
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

char	*get_next_line(int fd);
int		skip_char(char *str, char to_skip);
void	free_data(t_data *data);

#endif
