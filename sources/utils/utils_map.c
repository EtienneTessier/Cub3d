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

static void	replace_player(char **map2d)
{
	int	y;
	int	x;

	y = -1;
	while (map2d[++y])
	{
		x = -1;
		while (map2d[y][++x])
		{
			if (map2d[y][x] == 'S' || map2d[y][x] == 'N' || \
					map2d[y][x] == 'E' || map2d[y][x] == 'W')
				return ((void)(map2d[y][x] = '0'));
		}
	}
}

static int	is_in_char_arround(char **map2d, int y, int x)
{
	if ((map2d[y + 1][x] != '0' && map2d[y + 1][x] != ' ') || \
		(map2d[y - 1][x] != '0' && map2d[y - 1][x] != ' ') || \
		(map2d[y][x + 1] != '0' && map2d[y][x + 1] != ' ') || \
		(map2d[y][x - 1] != '0' && map2d[y][x - 1] != ' '))
		return (1);
	return (0);
}

int	check_space_inside(char **map2d)
{
	int	y;
	int	x;

	y = -1;
	replace_player(map2d);
	while (map2d[++y])
	{
		x = -1;
		while (map2d[y][++x])
		{
			if (map2d[y][x] == ' ' && is_in_char_arround(map2d, y, x))
				return (ft_putendl_fd(ERR_MAP_OPEN_INSIDE, 2), 1);
		}
	}
	return (0);
}
