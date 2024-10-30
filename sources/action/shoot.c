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

// static int	is_on_enemy(int shoot_x, int shoot_y, t_enemy enemy)
// {
// 	ft_printf("test\n");
// 	printf("enemy.x = %f, enemy.y = %f\n", enemy.x, enemy.y);
// 	printf("shoot_x = %d, shoot_y = %d\n", shoot_x, shoot_y);
// 	if ((shoot_x == (int)enemy.x) && (shoot_y == (int)enemy.y))
// 		return (printf("touche\n"), 1);
// 	return (0);
// }

// int	shoot(t_player player, t_data *data)
// {
// 	int		i;
// 	int		shoot_x;
// 	int		shoot_y;
// 	double	distance;

// 	i = -1;
// 	while (++i < data->ennemis_count)
// 	{
// 		shoot_x = player.dir_x;
// 		shoot_y = player.dir_y;
// 		distance = ((player.x - shoot_x) * (player.x - shoot_x) + \
// 			(player.y - shoot_y) * (player.y - shoot_y));
// 		while (distance <= data->ennemis[i].distance)
// 		{
// 			if (is_on_enemy(shoot_x, shoot_y, data->ennemis[i]))
// 				return (1);
// 			shoot_x += player.dir_x;
// 			shoot_y += player.dir_y;
// 			distance = ((player.x - shoot_x) * (player.x - shoot_x) + \
// 				(player.y - shoot_y) * (player.y - shoot_y));
// 		}
// 	}
// 	return (0);
// }
