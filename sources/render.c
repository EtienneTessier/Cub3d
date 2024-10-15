/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:41:15 by etessier          #+#    #+#             */
/*   Updated: 2024/10/15 11:41:16 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	load_tile(char c, t_img *img, int *x, int *y)
{
	int tile_x;
	int tile_y;

	tile_y = 0;
	while (tile_y < TILE_SIZE)
	{
		tile_x = 0;
		while (tile_x < TILE_SIZE)
		{
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
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
	int x;
	int	y;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			my_mlx_pixel_put(data->img, (data->player.x * TILE_SIZE) + x, (data->player.y * TILE_SIZE) + y, ORA_PIXEL);
			x++;
		}
		y++;
	}
}

int	load_map_img(t_data *data)
{
	size_t	i;
	size_t	j;
	int	y;
	int	x;

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
	mlx_put_image_to_window(data->mlx, data->win,data->img->img, 0, 0);
	return (0);
}

void	load_img(t_img *img)
{
	int	y;
	int	x;
	int	colors[8] = {RED_PIXEL, ORA_PIXEL, YEL_PIXEL, GRE_PIXEL, GRI_PIXEL, DBL_PIXEL, PUR_PIXEL, BLA_PIXEL};

	y = ((x = 0));
	while (y < SCR_HEIGHT)
	{
		x = 0;
		while (x < SCR_WIDTH)
		{
			my_mlx_pixel_put(img, x, y, colors[y % 8]);
			x++;
		}
		y++;
	}
}
