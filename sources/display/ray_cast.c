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

static void	find_delta_side_dist(t_ray *ray, t_data *data)
{
	ray->delta_dist_x = ((ray->delta_dist_y = (double)__LONG_MAX__));
	if (ray->ray_dir_x)
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y)
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_distx = (data->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distx = (ray->map_x + 1 - data->player.x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_disty = (data->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_disty = (ray->map_y + 1 - data->player.y) * ray->delta_dist_y;
	}
}

static void	find_wall_hit(t_ray *ray, t_data *data)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map->map2d[ray->map_y][ray->map_x] > '0')
			ray->hit = 1;
	}
}

static void	find_wall_tex_pos(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_distx - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_disty - ray->delta_dist_y;
	ray->line_height = (int)(SCR_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = (-ray->line_height / 2) + (SCR_HEIGHT / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (SCR_HEIGHT / 2);
	if (ray->draw_end >= SCR_HEIGHT)
		ray->draw_end = SCR_HEIGHT - 1;

	if (ray->side == 0)
		ray->wall_x = data->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = data->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)data->txr->width);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || \
			(ray->side == 1 && ray->ray_dir_y > 0))
		ray->tex_x = data->txr->width - ray->tex_x - 1;
	ray->step = 1.0 * data->txr->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - SCR_HEIGHT / 2 + ray->line_height / 2) \
		* ray->step;
}

// side == 1 && dir_y > 0 --> S
// side == 1 && dir_y < 0 --> N
// side == 0 && dir_x > 0 --> E
// side == 0 && dir_x < 0 --> W
static void	load_textures(t_ray *ray, t_data *data)
{
	if (ray->side == 1)
	{
		if (ray->ray_dir_y > 0)
			ray->txr = data->txr->south;
		else
			ray->txr = data->txr->north;
	}
	else
	{
		if (ray->ray_dir_x > 0)
			ray->txr = data->txr->east;
		else
			ray->txr = data->txr->west;
	}
	load_col_txr(ray, data);
}

int	ray_cast(t_data *data)
{
	t_ray	ray;

	ray.x = 0;
	while (ray.x < SCR_WIDTH)
	{
		ray.camera_x = 2 * ray.x / (double)SCR_WIDTH - 1;
		ray.ray_dir_x = data->player.dir_x + data->player.plan_x * ray.camera_x;
		ray.ray_dir_y = data->player.dir_y + data->player.plan_y * ray.camera_x;
		ray.map_x = (int)data->player.x;
		ray.map_y = (int)data->player.y;
		find_delta_side_dist(&ray, data);
		find_wall_hit(&ray, data);
		find_wall_tex_pos(&ray, data);
		if (DEBUG)
			load_color(&ray, data);
		else
			load_textures(&ray, data);
		ray.x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}
