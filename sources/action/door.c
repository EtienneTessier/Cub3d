/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:18:40 by tkara2            #+#    #+#             */
/*   Updated: 2024/11/05 15:18:41 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	door(t_player *player, t_data *data)
{
	double	x_pos;
	double	y_pos;

	x_pos = player->x + player->dir_x;
	y_pos = player->y + player->dir_y;
	if (data->map->map2d[(int)y_pos][(int)x_pos] == 'D')
		data->map->map2d[(int)y_pos][(int)x_pos] = 'd';
	else if (data->map->map2d[(int)y_pos][(int)x_pos] == 'd')
		data->map->map2d[(int)y_pos][(int)x_pos] = 'D';
	return (0);
}
