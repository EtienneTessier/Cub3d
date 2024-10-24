/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:54:56 by etessier          #+#    #+#             */
/*   Updated: 2024/10/24 13:54:57 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	get_player_dir(char c, t_data *data)
{
	data->player.dir_x = ((data->player.dir_y = 0));
	data->player.plan_x = ((data->player.plan_y = 0));
	if (c == 'W')
	{
		data->player.dir_x = -1.01;
		data->player.plan_y = -0.66;
	}
	else if (c == 'E')
	{
		data->player.dir_x = 1.01;
		data->player.plan_y = 0.66;
	}
	else if (c == 'S')
	{
		data->player.dir_y = 1.01;
		data->player.plan_x = -0.66;
	}
	else if (c == 'N')
	{
		data->player.dir_y = -1.01;
		data->player.plan_x = 0.66;
	}
}

void	find_player(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map->map2d[y])
	{
		x = 0;
		while (data->map->map2d[y][x])
		{
			if (data->map->map2d[y][x] == 'N' || \
				data->map->map2d[y][x] == 'S' || \
				data->map->map2d[y][x] == 'E' || \
				data->map->map2d[y][x] == 'W')
			{
				data->player.x = x + 0.5;
				data->player.y = y + 0.5;
				get_player_dir(data->map->map2d[y][x], data);
				data->map->map2d[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
