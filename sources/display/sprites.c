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

static void	find_enemy_pos(int i, t_data *data, t_sprite *sprite)
{
	sprite->x = data->ennemis[i].x - data->player.x;
	sprite->y = data->ennemis[i].y - data->player.y;
	sprite->inv_det = 1.0 / (data->player.plan_x * data->player.dir_y - \
		data->player.dir_x * data->player.plan_y);
	sprite->transform_x = sprite->inv_det * (data->player.dir_y * sprite->x - data->player.dir_x * sprite->y);
	sprite->transform_y = sprite->inv_det * (-data->player.plan_y * sprite->x + data->player.plan_x * sprite->y);
	sprite->screen_x = (int)((SCR_WIDTH / 2) * (1 + sprite->transform_x / sprite->transform_y));
}

static void	find_draw_pos_size(t_sprite *sprite)
{
		sprite->height = abs((int)(SCR_HEIGHT / sprite->transform_y));
		sprite->draw_start_y = -sprite->height / 2 + SCR_HEIGHT / 2;
		if (sprite->draw_start_y < 0)
			sprite->draw_start_y = 0;
		sprite->draw_end_y = sprite->height / 2 + SCR_HEIGHT / 2;
		if (sprite->draw_end_y >= SCR_HEIGHT)
			sprite->draw_end_y = SCR_HEIGHT - 1;
		sprite->width = abs((int)(SCR_HEIGHT / sprite->transform_y));

		sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
		if (sprite->draw_start_x < 0)
			sprite->draw_start_x = 0;
		sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
		if (sprite->draw_end_x >= SCR_WIDTH)
			sprite->draw_end_x = SCR_WIDTH - 1;
}

static void	get_texture_terro(int i, t_sprite *sprite, t_data *data, t_ray *ray)
{
	if (!data->ennemis[i].alive)
		ray->txr = data->txr->dead;
	else if (sprite->distance[i] > 100)
		ray->txr = data->txr->right;
	else
		ray->txr = data->txr->left;
}

static void	load_enemy(t_sprite *sprite, t_ray ray, t_data *data)
{
	int	y;

	sprite->stripe = sprite->draw_start_x;
	while (sprite->stripe < sprite->draw_end_x)
	{
		ray.tex_x = (int)(256 * (sprite->stripe - (-sprite->width / 2 + sprite->screen_x)) *
			BEN_WIDTH / sprite->width) / 256;
		y = sprite->draw_start_y;
		if (sprite->transform_y > 0 && sprite->stripe > 0 && sprite->stripe < SCR_WIDTH &&
				sprite->transform_y < ray.z_buffer[sprite->stripe])
			while (y < sprite->draw_end_y)
			{
				ray.tex_y = ((y - SCR_HEIGHT / 2 + sprite->height / 2) * BEN_HEIGHT) / sprite->height;
				if (ray.txr[ray.tex_y * BEN_WIDTH + ray.tex_x] != 0xff0000)
					my_mlx_pixel_put(data->img, sprite->stripe, y, ray.txr[ray.tex_y *
						BEN_WIDTH + ray.tex_x]);
				y++;
			}
		sprite->stripe += 1;
	}
}

void	print_sprites(t_data *data, t_ray ray, t_player player)
{
	t_sprite	*sprite;
	int			i;

	sprite = ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
		exit_pgm(data, 1);
	i = -1;
	while (++i < data->ennemis_count)
	{
		sprite->distance[i] = ((player.x - data->ennemis[i].x) * (player.x - data->ennemis[i].x) +
			(player.y - data->ennemis[i].y) * (player.y - data->ennemis[i].y));
		data->ennemis[i].distance = sprite->distance[i];
	}
	sort_sprites(sprite->distance, data->ennemis, data->ennemis_count);
	i = -1;
	while (++i < data->ennemis_count)
	{
		find_enemy_pos(i, data, sprite);
		find_draw_pos_size(sprite);
		get_texture_terro(i, sprite, data, &ray);
		load_enemy(sprite, ray, data);
	}
	free(sprite);
}
