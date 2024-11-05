/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:28:21 by etessier          #+#    #+#             */
/*   Updated: 2024/10/30 09:28:22 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Projeter zone autour du joueur
// Projeter le rayon direction du joueur
// Si rayon dans la zone -> dead

static int	is_on_enemy(int shoot_x, int shoot_y, t_enemy enemy)
{
	if ((shoot_x == (int)enemy.x) && (shoot_y == (int)enemy.y))
		return (1);
	return (0);
}

static int	is_on_wall(int shoot_x, int shoot_y, char **map)
{
	if (map[shoot_y][shoot_x] == '1')
		return (1);
	return (0);
}

int	shoot(t_player *player, t_data *data)
{
	int		i;
	double	shoot_x;
	double	shoot_y;
	double	distance;

	i = -1;
	while (++i < data->ennemis_count)
	{
		shoot_x = player->x;
		shoot_y = player->y;
		distance = 0;
		while (distance <= data->ennemis[i].distance && data->ennemis[i].alive)
		{
			if (is_on_wall(shoot_x, shoot_y, data->map->map2d))
				break ;
			if (is_on_enemy(shoot_x, shoot_y, data->ennemis[i]))
				return ((data->ennemis[i].alive = 0), 1);
			shoot_x += player->dir_x / 2;
			shoot_y += player->dir_y / 2;
			distance = ((player->x - shoot_x) * (player->x - shoot_x) + \
				(player->y - shoot_y) * (player->y - shoot_y));
		}
	}
	return (0);
}
