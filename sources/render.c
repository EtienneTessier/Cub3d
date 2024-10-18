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
	img->addr[y * img->line_length + x] = color;
	// *(unsigned int *)dst = color;
}

void	load_col(int x, t_ray ray, int color, t_data *data)
{
	int	y;

	y = 0;
	while (y < ray.draw_start)
	{
		my_mlx_pixel_put(data->img, x, y, BLA_PIXEL);
		y++;
	}
	while (y >= ray.draw_start && y <= ray.draw_end)
	{
		my_mlx_pixel_put(data->img, x, y, color);
		y++;
	}
	while (y < SCR_HEIGHT - 1)
	{
		my_mlx_pixel_put(data->img, x, y, DBL_PIXEL);
		y++;
	}
}

void	load_col_txr(t_ray ray, t_data *data)
{
	int	y;

	y = 0;
	while (y < ray.draw_start)
	{
		my_mlx_pixel_put(data->img, ray.x, y, BLA_PIXEL);
		y++;
	}
	while (y >= ray.draw_start && y <= ray.draw_end)
	{
		ray.tex_y = (int)ray.tex_pos & (TXR_HEIGHT - 1);
		ray.tex_pos += ray.step;
		data->img->addr[y * data->img->line_length + ray.x] = \
		ray.txr[ray.tex_y * 64 + ray.tex_x];
		y++;
	}
	while (y < SCR_HEIGHT - 1)
	{
		my_mlx_pixel_put(data->img, ray.x, y, DBL_PIXEL);
		y++;
	}
}
