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

#include "../../../includes/cub3d.h"

void	load_col_txr_b(t_ray *ray, t_data *data)
{
	int	y;

	y = -1;
	while (++y < ray->draw_start)
	{
		my_mlx_pixel_put(data->img, ray->x, y, data->txr->sky[y * \
			SCR_WIDTH + ray->x]);
	}
	while (y >= ray->draw_start && y <= ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (data->txr->width - 1);
		ray->tex_pos += ray->step;
		my_mlx_pixel_put(data->img, ray->x, y, ray->txr \
			[ray->tex_y * data->txr->width + ray->tex_x]);
		y++;
	}
}
