/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:16:22 by etessier          #+#    #+#             */
/*   Updated: 2024/10/15 15:16:23 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move_forward(t_player *player, t_data *data)
{
	if (data->map->map2d[(int)player->y] \
			[(int)(player->x + (player->dir_x * SPEED))] == '0')
		player->x += player->dir_x * SPEED;
	if (data->map->map2d[(int)(player->y + (player->dir_y * SPEED))] \
			[(int)player->x] == '0')
		player->y += player->dir_y * SPEED;
}

static void	move_backward(t_player *player, t_data *data)
{
	if (data->map->map2d[(int)player->y] \
			[(int)(player->x - (player->dir_x * SPEED))] == '0')
		player->x -= player->dir_x * SPEED;
	if (data->map->map2d[(int)(player->y - (player->dir_y * SPEED))] \
			[(int)player->x] == '0')
		player->y -= player->dir_y * SPEED;
}

static void	move_left(t_player *player, t_data *data)
{
	if (data->map->map2d[(int)player->y] \
			[(int)(player->x - (player->plan_x * SPEED))] == '0')
		player->x -= player->plan_x * SPEED;
	if (data->map->map2d[(int)(player->y - (player->plan_y * SPEED))] \
			[(int)player->x] == '0')
		player->y -= player->plan_y * SPEED;
}

static void	move_right(t_player *player, t_data *data)
{
	if (data->map->map2d[(int)player->y] \
			[(int)(player->x + (player->plan_x * SPEED))] == '0')
		player->x += player->plan_x * SPEED;
	if (data->map->map2d[(int)(player->y + (player->plan_y * SPEED))] \
			[(int)player->x] == '0')
		player->y += player->plan_y * SPEED;
}

int	handle_key(int key_code, t_data *data)
{
	if (key_code == W)
		move_forward(&data->player, data);
	else if (key_code == S)
		move_backward(&data->player, data);
	else if (key_code == A)
		move_left(&data->player, data);
	else if (key_code == D)
		move_right(&data->player, data);
	else if (key_code == LEFT)
		rotate_left(&data->player);
	else if (key_code == RIGHT)
		rotate_right(&data->player);
	else if (key_code == ESC)
		exit_pgm(data, 0);
	return (0);
}
