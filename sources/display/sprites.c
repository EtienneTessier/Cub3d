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

void	print_sprites(t_data *data, t_ray ray, t_player player)
{
	t_sprite	sprite;
	int			i;
	int			y;

	i = -1;
	while (++i < data->ennemis_count)
		sprite.distance[i] = ((player.x - data->ennemis[i].x) * (player.x - data->ennemis[i].x) +
			(player.y - data->ennemis[i].y) * (player.y - data->ennemis[i].y));
	sort_sprites(sprite.distance, data->ennemis, data->ennemis_count);
	i = 0;
	while (i < data->ennemis_count)
	{
		// printf("i = %d\n", i);
		// printf("data->ennemis[i].id = %d\n", data->ennemis[i].id);
		// printf("data->ennemis[i].x = %f\n", data->ennemis[i].x);
		// printf("data->ennemis[i].y = %f\n", data->ennemis[i].y);
		// printf("sprite.distance[i] = %f\n", sprite.distance[i]);
		sprite.x = data->ennemis[i].x - player.x;
		sprite.y = data->ennemis[i].y - player.y;

		sprite.inv_det = 1.0 / (player.plan_x * player.dir_y - player.dir_x * player.plan_y);

		sprite.transform_x = sprite.inv_det * (player.dir_y * sprite.x - player.dir_x * sprite.y);
		sprite.transform_y = sprite.inv_det * (-player.plan_y * sprite.x + player.plan_x * sprite.y);

		sprite.screen_x = (int)((SCR_WIDTH / 2) * (1 + sprite.transform_x / sprite.transform_y));

		sprite.height = abs((int)(SCR_HEIGHT / sprite.transform_y));

		sprite.draw_start_y = -sprite.height / 2 + SCR_HEIGHT / 2;
		if (sprite.draw_start_y < 0)
			sprite.draw_start_y = 0;
		// printf("sprite.draw_start_y = %d\n", sprite.draw_start_y);

		sprite.draw_end_y = sprite.height / 2 + SCR_HEIGHT / 2;
		if (sprite.draw_end_y >= SCR_HEIGHT)
			sprite.draw_end_y = SCR_HEIGHT - 1;
		// printf("sprite.draw_end_y = %d\n", sprite.draw_end_y);

		sprite.width = abs((int)(SCR_HEIGHT / sprite.transform_y));
		// ft_printf("width enemy = %d\n", sprite.width);

		sprite.draw_start_x = -sprite.width / 2 + sprite.screen_x;
		if (sprite.draw_start_x < 0)
			sprite.draw_start_x = 0;
		// printf("sprite.draw_start_x = %d\n", sprite.draw_start_x);

		sprite.draw_end_x = sprite.width / 2 + sprite.screen_x;
		if (sprite.draw_end_x >= SCR_WIDTH)
			sprite.draw_end_x = SCR_WIDTH - 1;
		// printf("sprite.draw_end_x = %d\n", sprite.draw_end_x);

		if (sprite.distance[i] > 100)
			ray.txr = data->txr->right;
		else
			ray.txr = data->txr->left;
		sprite.stripe = sprite.draw_start_x;
		while (sprite.stripe < sprite.draw_end_x)
		{
			ray.tex_x = (int)(256 * (sprite.stripe - (-sprite.width / 2 + sprite.screen_x)) *
				BEN_WIDTH / sprite.width) / 256;

			// printf("ray.tex_x = %d\n", ray.tex_x);
			// printf("sprite.stripe = %d\n", sprite.stripe);
			y = sprite.draw_start_y;
			if (sprite.transform_y > 0 && sprite.stripe > 0 && sprite.stripe < SCR_WIDTH &&
					sprite.transform_y < ray.z_buffer[sprite.stripe])
				while (y < sprite.draw_end_y)
				{
					ray.tex_y = ((y - SCR_HEIGHT / 2 + sprite.height / 2) * BEN_HEIGHT) / sprite.height;
					// printf("ray.tex_y = %d\n", ray.tex_y);
					if (ray.txr[ray.tex_y * BEN_WIDTH + ray.tex_x] != 0xff0000)
						my_mlx_pixel_put(data->img, sprite.stripe, y, ray.txr[ray.tex_y *
							BEN_WIDTH + ray.tex_x]);
					y++;
				}
			sprite.stripe++;
		}
	i++;
	}
	// sleep(1);
	// ft_printf("\n\n\n");
}
