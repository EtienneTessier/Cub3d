/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:24:34 by etienne           #+#    #+#             */
/*   Updated: 2024/10/20 10:24:35 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_right(t_player *player)
{
	double	old_dir_x;
	double	old_plan_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(RSPEED) - \
		player->dir_y * sin(RSPEED);
	player->dir_y = old_dir_x * sin(RSPEED) + \
		player->dir_y * cos(RSPEED);
	old_plan_x = player->plan_x;
	player->plan_x = player->plan_x * cos(RSPEED) - \
		player->plan_y * sin(RSPEED);
	player->plan_y = old_plan_x * sin(RSPEED) + \
		player->plan_y * cos(RSPEED);
}

void	rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plan_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-RSPEED) - \
		player->dir_y * sin(-RSPEED);
	player->dir_y = old_dir_x * sin(-RSPEED) + \
		player->dir_y * cos(-RSPEED);
	old_plan_x = player->plan_x;
	player->plan_x = player->plan_x * \
		cos(-RSPEED) - player->plan_y * sin(-RSPEED);
	player->plan_y = old_plan_x * sin(-RSPEED) + \
		player->plan_y * cos(-RSPEED);
}

int	mouse_move(int x, int y, t_data *data)
{
	if (x == SCR_WIDTH / 2 && y == SCR_HEIGHT / 2)
		return (EXIT_SUCCESS);
	if (x >= SCR_WIDTH / 2)
		rotate_right(&data->player);
	else
		rotate_left(&data->player);
	mlx_mouse_move(data->mlx, data->win, SCR_WIDTH / 2, SCR_HEIGHT / 2);
	return (EXIT_SUCCESS);
}
