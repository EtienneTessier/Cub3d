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
	int	dst;

	dst = y * (img->line_length / 4) + x;
	img->addr[dst] = color;
}

void	load_col(t_ray *ray, t_data *data)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(data->img, ray->x, y, BLA_PIXEL);
		y++;
	}
	while (y >= ray->draw_start && y <= ray->draw_end)
	{
		my_mlx_pixel_put(data->img, ray->x, y, data->txtr->color);
		y++;
	}
	while (y < SCR_HEIGHT - 1)
	{
		my_mlx_pixel_put(data->img, ray->x, y, DBL_PIXEL);
		y++;
	}
}

void	load_col_txr(t_ray *ray, t_data *data)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(data->img, ray->x, y, BLA_PIXEL);
		y++;
	}
	while (y >= ray->draw_start && y <= ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (data->txtr->width - 1);
		ray->tex_pos += ray->step;
		my_mlx_pixel_put(data->img, ray->x, y, ray->txr \
			[ray->tex_y * data->txtr->width + ray->tex_x]);
		y++;
	}
	while (y < SCR_HEIGHT)
	{
		my_mlx_pixel_put(data->img, ray->x, y, DBL_PIXEL);
		y++;
	}
}
