/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 08:04:32 by etienne           #+#    #+#             */
/*   Updated: 2024/10/26 08:04:33 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	swap_sprites(int *order, double *distance, int pos)
{
	int		order_tmp;
	double	distance_tmp;

	order_tmp = order[pos];
	order[pos] = order[pos + 1];
	order[pos + 1] = order_tmp;
	distance_tmp = distance[pos];
	distance[pos] = distance[pos + 1];
	distance[pos + 1] = distance_tmp;
}

static void	sort_sprites(int *order, double *distance, int sprites_count)
{
	int	i;
	int j;

	i = 0;
	while (i < sprites_count - 1)
	{
		j = i;
		while (j < sprites_count - 1)
		{
			if (distance[j] < distance[j + 1])
				swap_sprites(order, distance, j);
			j++;
		}
		i++;
	}
}

void	print_sprites(t_data *data, t_ray ray, t_player player)
{
	t_sprite	sprite;
	int			i;

	sprite.order = ft_calloc(data->sprites_count, sizeof(int));
	if (!sprite.order)
		exit_pgm(data);
	sprite.distance = ft_calloc(data->sprites_count, sizeof(double));
	if (!sprite.distance)
		exit_pgm(data);
	i = 0;
	while (i < data->sprites_count)
	{
		sprite.order[i] = i;
		sprite.distance[i] = ((player.x - data->sprites[i].x) * (player.x - data->sprites[i].x) + (player.y - data->sprites[i].y) * player.y - data->sprites[i].y);
		i++;
	}
	sort_sprites(sprite.order, sprite.distance, data->sprites_count);
	i = 0;
	while (i < data->sprites_count)
	{
		sprite.x = data->sprites[i].x - player.x;
		sprite.y = data->sprites[i].y - player.y;

		sprite.inv_det = 1.0 / (player.plan_x * player.dir_y - player.dir_x * player.plan_y);

		sprite.transform_x = sprite.inv_det * (player.dir_y * sprite.x - player.dir_x * sprite.y);
		sprite.transform_y = sprite.inv_det * (-player.plan_y * sprite.x + player.dir_x * sprite.y);

		sprite.screen_x = (int)((SCR_WIDTH / 2) * (1 + sprite.transform_x / sprite.transform_y));

		sprite.height = abs((int)(SCR_HEIGHT / sprite.transform_y));

		sprite.draw_start_y = -sprite.height / 2 + SCR_HEIGHT / 2;
		if (sprite.draw_start_y < 0)
			sprite.draw_start_y = 0;
		sprite.draw_end_y = sprite.height / 2 + SCR_HEIGHT / 2;
		if (sprite.draw_end_y >= SCR_HEIGHT)
			sprite.draw_start_y = SCR_HEIGHT - 1;

		sprite.width = abs((int)(SCR_HEIGHT / sprite.transform_y));
		sprite.draw_start_x = -sprite.width / 2 + sprite.screen_x;
		if (sprite.draw_start_x < 0)
			sprite.draw_start_x = 0;
		sprite.draw_end_x = sprite.width / 2 + sprite.screen_x;
		if (sprite.draw_end_x >= SCR_WIDTH)
			sprite.draw_end_x = SCR_WIDTH - 1;
		sprite.stripe = sprite.draw_start_x;
		while (sprite.stripe < sprite.draw_end_x)
		{
			ray.tex_x = (int)(256 * (sprite.stripe - (-sprite.width / 2 + sprite.screen_x)) * SPRITE_SIZE / sprite.width) / 256;
			if (sprite.transform_y > 0 && sprite.stripe > 0 && sprite.stripe < SCR_WIDTH && sprite.transform_y < ray.z_buffer[sprite.stripe])
				while (sprite.draw_start_y < sprite.draw_end_y)
				{
					int d;
					d = sprite.draw_start_y * 256 - SCR_HEIGHT * 128 + sprite.height * 128;
					ray.tex_y = ((d * SPRITE_SIZE) / sprite.height) / 256;
					my_mlx_pixel_put(data->img, sprite.stripe, sprite.draw_start_y, data->sprites[i].txr[ray.tex_y * SPRITE_SIZE + ray.tex_x]);
					sprite.draw_start_y++;
				}
			sprite.stripe++;
		}
	i++;
	}
}
