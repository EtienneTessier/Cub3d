/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:17 by etessier          #+#    #+#             */
/*   Updated: 2024/10/11 16:47:18 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*load_map(t_data *data)
{
	char	*str;
	char	*map1d;

	while (1)
	{
		map1d = get_next_line(data->map->fd);
		if (!map1d || map1d[0] == '\0')
			return (map1d);
		if (map1d[0] != '\n')
			break ;
		free(map1d);
	}
	while (1)
	{
		str = get_next_line(data->map->fd);
		if (!str || str[0] == '\0')
			return (map1d);
		map1d = ft_join(map1d, str, ft_strlen(str));
		free(str);
		if (!map1d)
			return (NULL);
	}
}

static void	get_player_dir(char c, t_data *data)
{
	data->player.dir_x = ((data->player.dir_y = 0));
	data->player.plan_x = ((data->player.plan_y = 0));
	if (c == 'W') //E
	{
		// data->player.dir_y = -1;
		data->player.dir_x = -1;
		data->player.plan_y = 0.66;
	}
	else if (c == 'E') //W
	{
		// data->player.dir_y = 1;
		data->player.dir_x = 1;
		data->player.plan_y = -0.66;
	}
	else if (c == 'S')
	{
		// data->player.dir_x = 1;
		data->player.dir_y = 1;
		data->player.plan_x = 0.66;
	}
	else if (c == 'N')
	{
		// data->player.dir_x = -1;
		data->player.dir_y = -1;
		data->player.plan_x = -0.66;
	}
	// printf("data->player.dir_x = %f\n", data->player.dir_x);
	// printf("data->player.dir_y = %f\n", data->player.dir_y);
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
				data->player.x = x;
				data->player.y = y;
				get_player_dir(data->map->map2d[y][x], data);
				data->map->map2d[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
