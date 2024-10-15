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
	// if (data->map->map2d[(int)player->y][(int)(player->x + (player->dir_x * SPEED))] == '0')
	(void)data;
	player->x += player->dir_x * SPEED;
	// if (data->map->map2d[(int)(player->y + (player->dir_y * SPEED))][(int)player->x] == '0')
	player->y += player->dir_y * SPEED;
}

static void	move_backward(t_player *player, t_data *data)
{
	// if (data->map->map2d[(int)player->y][(int)(player->x - (player->dir_x * SPEED))] == '0')
	(void)data;
	player->x -= player->dir_x * SPEED;
	// if (data->map->map2d[(int)(player->y - (player->dir_y * SPEED))][(int)player->x] == '0')
	player->y -= player->dir_y * SPEED;
}

static void	rotate_right(t_player *player)
{
	double	old_dir_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-RSPEED) - player->dir_y * sin(-RSPEED);
	player->dir_y = old_dir_x * sin(-RSPEED) + player->dir_y * cos(-RSPEED);
	// printf("player->dir_x = %f\n", player->dir_x);
	// printf("player->dir_y = %f\n", player->dir_y);
}

static void	rotate_left(t_player *player)
{
	double	old_dir_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(RSPEED) - player->dir_y * sin(RSPEED);
	player->dir_y = old_dir_x * sin(RSPEED) + player->dir_y * cos(RSPEED);
	// printf("player->dir_x = %f\n", player->dir_x);
	// printf("player->dir_y = %f\n", player->dir_y);
}

int	handle_key(int key_code, t_data *data)
{
	if (key_code == W)
		move_forward(&data->player, data);
	else if (key_code == S)
		move_backward(&data->player, data);
	else if (key_code == A)
		rotate_left(&data->player);
	else if (key_code == D)
		rotate_right(&data->player);
	else if (key_code == ESC)
		exit_pgm(data);
	return (0);
}
