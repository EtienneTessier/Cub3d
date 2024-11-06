/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:56:27 by etienne           #+#    #+#             */
/*   Updated: 2024/11/05 15:56:28 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_floor_cast(t_data *data, t_floor *floor)
{
	floor->ray_dir_x0 = data->player.dir_x - data->player.plan_x;
	floor->ray_dir_y0 = data->player.dir_y - data->player.plan_y;
	floor->ray_dir_x1 = data->player.dir_x + data->player.plan_x;
	floor->ray_dir_y1 = data->player.dir_y + data->player.plan_y;
	floor->pos = floor->y - SCR_HEIGHT / 2;
	floor->pos_z = 0.5 * SCR_HEIGHT;
	floor->row_distance = floor->pos_z / floor->pos;
	floor->step_x = floor->row_distance * (floor->ray_dir_x1
			- floor->ray_dir_x0) / SCR_WIDTH;
	floor->step_y = floor->row_distance * (floor->ray_dir_y1
			- floor->ray_dir_y0) / SCR_WIDTH;
	floor->floor_x = data->player.x + floor->row_distance * floor->ray_dir_x0;
	floor->floor_y = data->player.y + floor->row_distance * floor->ray_dir_y0;
}

void	load_floor(t_data *data)
{
	t_floor	floor;

	floor.y = SCR_HEIGHT / 2;
	while (floor.y < SCR_HEIGHT)
	{
		init_floor_cast(data, &floor);
		floor.x = 0;
		while (floor.x < SCR_WIDTH)
		{
			floor.cell_x = (int)(floor.floor_x);
			floor.cell_y = (int)(floor.floor_y);
			floor.tex_x = (int)(data->txr->width * (floor.floor_x
						- floor.cell_x)) & (data->txr->width - 1);
			floor.tex_y = (int)(data->txr->height * (floor.floor_y
						- floor.cell_y)) & (data->txr->height - 1);
			floor.floor_x += floor.step_x;
			floor.floor_y += floor.step_y;
			my_mlx_pixel_put(data->img, floor.x, floor.y,
					data->txr->floor_txr[data->txr->width * floor.tex_y
					+ floor.tex_x]);
			floor.x++;
		}
		floor.y++;
	}
}
