/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:27:10 by etienne           #+#    #+#             */
/*   Updated: 2024/10/16 16:27:11 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ray_cast(t_data *data)
{
	t_ray	ray;
	// int color;

	ray.x = 0;
	while (ray.x < SCR_WIDTH)
	{
		ray.camera_x = 2 * ray.x / (double)SCR_WIDTH - 1;
		ray.ray_dir_x = data->player.dir_x + data->player.plan_x * ray.camera_x;
		ray.ray_dir_y = data->player.dir_y + data->player.plan_y * ray.camera_x;
		// printf("ray.ray_dir_x = %f\n", ray.ray_dir_x);
		// printf("ray.ray_dir_y = %f\n", ray.ray_dir_y);

		ray.map_x = (int)data->player.x;
		ray.map_y = (int)data->player.y;
		// printf("data->player.x = %f\n", data->player.x);
		// printf("data->player.y = %f\n", data->player.y);
		// ft_printf("ray.map_x = %d\n", ray.map_x);
		// ft_printf("ray.map_y = %d\n", ray.map_y);

		ray.delta_dist_x = ((ray.delta_dist_y = (double)__LONG_MAX__));
		if (ray.ray_dir_x)
			ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
		if (ray.ray_dir_y)
			ray.delta_dist_y = fabs(1 / ray.ray_dir_y);
		// printf("ray.delta_dist_x = %f\n", ray.delta_dist_x);
		// printf("ray.delta_dist_y = %f\n", ray.delta_dist_y);

		if (ray.ray_dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (data->player.x - ray.map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - data->player.x) * ray.delta_dist_x;
		}
		if (ray.ray_dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (data->player.y - ray.map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1 - data->player.y) * ray.delta_dist_y;
		}
		// printf("ray.side_dist_x = %f\n", ray.side_dist_x);
		// printf("ray.side_dist_y = %f\n", ray.side_dist_y);
		ray.hit = 0;
		while (ray.hit == 0)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}
			if (data->map->map2d[ray.map_y][ray.map_x] > '0')
				ray.hit = 1;
		}

		// printf("ray.side_dist_x = %f\n", ray.side_dist_x);
		// printf("ray.side_dist_y = %f\n", ray.side_dist_y);
		// printf("ray.delta_dist_x = %f\n", ray.delta_dist_x);
		// printf("ray.delta_dist_y = %f\n", ray.delta_dist_y);
		if (ray.side == 0)
			ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
		// ft_printf("ray.perp_wall_dist = %d\n", ray.perp_wall_dist);

		ray.line_height = (int)(SCR_HEIGHT / ray.perp_wall_dist);
		// ft_printf("ray.line_height = %d\n", ray.line_height);

		ray.draw_start = (-ray.line_height / 2) + (SCR_HEIGHT / 2);
		// ft_printf("1. ray.draw_start = %d\n", ray.draw_start);
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		// ft_printf("ray.draw_start = %d\n", ray.draw_start);

		ray.draw_end = (ray.line_height / 2) + (SCR_HEIGHT / 2);
		// ft_printf("1. ray.draw_end = %d\n", ray.draw_end);
		if (ray.draw_end >= SCR_HEIGHT)
			ray.draw_end = SCR_HEIGHT - 1;
		// ft_printf("ray.draw_end = %d\n\n", ray.draw_end);

		if (ray.side == 0)
			ray.wall_x = data->player.y + ray.perp_wall_dist * ray.ray_dir_y;
		else
			ray.wall_x = data->player.x + ray.perp_wall_dist * ray.ray_dir_x;
		ray.wall_x -= floor(ray.wall_x);
		ray.tex_x = (int)(ray.wall_x * TXR_WIDTH);
		if ((ray.side == 0 && ray.ray_dir_x > 0) || (ray.side == 1 && ray.ray_dir_y < 0))
			ray.tex_x = TXR_WIDTH - ray.tex_x - 1;

		ray.step = 1.0 * (TXR_HEIGHT / ray.line_height);

		ray.tex_pos = (ray.draw_start - SCR_HEIGHT / 2 + ray.line_height / 2) * ray.step;
		// side == 1 && dir_y > 0 --> S
		// side == 1 && dir_y < 0 --> N
		// side == 0 && dir_x > 0 --> E
		// side == 0 && dir_x < 0 --> W
		// if (ray.side == 1)
		// {
		// 	if (ray.ray_dir_y > 0)
		// 		color = GRI_PIXEL;
		// 	else
		// 		color = ORA_PIXEL;
		// }
		// else
		// {
		// 	if (ray.ray_dir_x > 0)
		// 		color = WHI_PIXEL;
		// 	else
		// 		color = GRE_PIXEL;
		// }
		// load_col(ray.x, ray, color, data);
		if (ray.side == 1)
		{
			if (ray.ray_dir_y > 0)
				ray.txr = data->txtr->south;
			else
				ray.txr = data->txtr->north;
		}
		else
		{
			if (ray.ray_dir_x > 0)
				ray.txr = data->txtr->east;
			else
				ray.txr = data->txtr->west;
		}
		load_col_txr(ray, data);
		ray.x += 1;
	}
	mlx_put_image_to_window(data->mlx, data->win,data->img->img, 0, 0);
	sleep(1);
	return (0);
}
