/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:39:13 by etessier          #+#    #+#             */
/*   Updated: 2024/10/24 12:39:14 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

static void	load_tile(char c, t_img *img, int x, int y)
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
				my_mlx_pixel_put(img, x + tile_x + TILE_SIZE, y + tile_y + TILE_SIZE, GRI_PIXEL);
			else if (c == '1')
				my_mlx_pixel_put(img, x + tile_x + TILE_SIZE, y + tile_y + TILE_SIZE, WHI_PIXEL);
			tile_x++;
		}
		tile_y++;
	}
}

static void	load_player(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < 6)
	{
		x = 0;
		while (x < 6)
		{
			my_mlx_pixel_put(img, x + TILE_SIZE * 6.4, y + TILE_SIZE * 6.4, RED_PIXEL);
			x++;
		}
		y++;
	}
}

void	print_minimap(t_img *img, t_player player, t_data *data)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;

	start_x = (int)player.x - 5;
	start_y = (int)player.y - 1;
	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			if (start_x + x <= (int)data->map->width && start_x + x >= 0)
				load_tile(data->map->minimap[start_y + y][start_x + x], img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	load_player(img);
}
