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
	// ft_printf("test\n");
	// printf("enemy.x = %f, enemy.y = %f\n", enemy.x, enemy.y);
	// printf("shoot_x = %d, shoot_y = %d\n", shoot_x, shoot_y);
	if ((shoot_x == (int)enemy.x) && (shoot_y == (int)enemy.y))
		return (printf("touche\n"), 1);
	return (0);
}

int	shoot(t_player *player, t_data *data)
{
	int		i;
	int		shoot_x;
	int		shoot_y;
	double	distance;

	ft_printf("shoot\n");
	i = -1;
	while (++i < data->ennemis_count)
	{
		shoot_x = player->x;
		shoot_y = player->y;
		distance = 0;
		// printf("distance = %f\n", distance);
		// printf("data->ennemis[%d].distance = %f\n", i, data->ennemis[i].distance);
		// ft_printf("shoot_x = %d\n", shoot_x);
		// ft_printf("shoot_y = %d\n", shoot_y);
		while (distance <= data->ennemis[i].distance && data->ennemis[i].alive)
		{
			if (is_on_enemy(shoot_x, shoot_y, data->ennemis[i]))
			{
				data->ennemis[i].alive = 0;
				return (1);
			}
			shoot_x += player->dir_x;
			shoot_y += player->dir_y;
			distance = ((player->x - shoot_x) * (player->x - shoot_x) + \
				(player->y - shoot_y) * (player->y - shoot_y));
		}
	}
	return (0);
}
