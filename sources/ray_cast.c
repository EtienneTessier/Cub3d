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

void	ray_cast(t_data *data, t_ray *ray)
{
	int	x;
	int	w;

	w = 100;
	x = -1;
	while (x < w)
	{
		ray->camera_x = 2 * x / (double)w - 1;
		ray->ray_dir_x = data->player.dir_x + ray->plan_x * ray->camera_x;
		ray->ray_dir_y = data->player.dir_y + ray->plan_y * ray->camera_x;

		ray->map_x = (int)data->player.x;
		ray->map_y = (int)data->player.y;

		ray->delta_dist_x = ((ray->delta_dist_y = __LONG_MAX__));
		if (ray->ray_dir_x)
			ray->delta_dist_x = abs(1 / ray->ray_dir_x);
		if (ray->ray_dir_y)
			ray->delta_dist_y = abs(1 / ray->ray_dir_y);
		if (ray->ray_dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (data->player.x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - data->player.x) * ray->delta_dist_x;
		}
		if (ray->ray_dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (data->player.y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (data->ray.map_y + 1 - data->player.y) * ray->delta_dist_y;
		}
		ray->hit = 0;
		while (ray->hit == 0)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			if (data->map->map2d[ray->map_y][ray->map_x] > '0')
				ray->hit = 1;
		}
	}
}
