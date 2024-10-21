/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:56:59 by etessier          #+#    #+#             */
/*   Updated: 2024/10/11 14:57:00 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map_2d(char **map2d)
{
	int	i;
	int	j;

	i = -1;
	while (map2d[++i])
	{
		j = -1;
		while (map2d[i][++j])
			ft_printf("%c", map2d[i][j]);
		ft_printf("\n");
	}
}

static void	load_tile(char c, t_img *img, int *x, int *y)
{
	int	tile_x;
	int	tile_y;

	tile_y = 0;
	while (tile_y < TILE_SIZE)
	{
		tile_x = 0;
		while (tile_x < TILE_SIZE)
		{
			if (c == '0')
				my_mlx_pixel_put(img, *x + tile_x, *y + tile_y, GRI_PIXEL);
			else if (c == '1')
				my_mlx_pixel_put(img, *x + tile_x, *y + tile_y, WHI_PIXEL);
			else
				my_mlx_pixel_put(img, *x + tile_x, *y + tile_y, DBL_PIXEL);
			tile_x++;
		}
		tile_y++;
	}
}

static void	load_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			my_mlx_pixel_put(data->img, (data->player.x * TILE_SIZE) + x, \
				(data->player.y * TILE_SIZE) + y, ORA_PIXEL);
			x++;
		}
		y++;
	}
}

int	load_map_img(t_data *data)
{
	size_t	i;
	size_t	j;
	int		y;
	int		x;

	y = ((x = 0));
	i = -1;
	while (data->map->map2d[++i])
	{
		j = -1;
		while (++j < data->map->width)
		{
			load_tile(data->map->map2d[i][j], data->img, &x, &y);
			x += TILE_SIZE;
		}
		y += TILE_SIZE - 1;
	}
	load_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

// side == 1 && dir_y > 0 --> S
// side == 1 && dir_y < 0 --> N
// side == 0 && dir_x > 0 --> E
// side == 0 && dir_x < 0 --> W
void	load_color(t_ray *ray, t_data *data)
{
	if (ray->side == 1)
	{
		if (ray->ray_dir_y > 0)
			data->txr->color = GRI_PIXEL;
		else
			data->txr->color = ORA_PIXEL;
	}
	else
	{
		if (ray->ray_dir_x > 0)
			data->txr->color = WHI_PIXEL;
		else
			data->txr->color = GRE_PIXEL;
	}
	load_col(ray, data);
}
