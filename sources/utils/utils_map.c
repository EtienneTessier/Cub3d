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
			if (map2d[y][x] == ' ' && (map2d[y + 1][x] == '0' ||
					map2d[y - 1][x] == '0' || map2d[y][x + 1] == '0' ||
					map2d[y][x - 1] == '0'))
				return (ft_putendl_fd(ERR_MAP_OPEN_INSIDE, 2), 1);
		}
	}
	return (0);
}

static int	init_minimap(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < 4)
	{
		data->map->minimap[i] = crea_row(' ', data->map->width);
		if (!data->map->minimap[i])
			return (ft_freesplit(data->map->minimap), 1);
	}
	i = -1;
	while (++i < data->map->height)
	{
		data->map->minimap[i + 4] = ft_strdup(data->map->map2d[i]);
		if (!data->map->minimap[i + 4])
			return (ft_freesplit(data->map->minimap), 1);
	}
	i = -1;
	while (++i < 4)
	{
		data->map->minimap[i + data->map->height + 4] = crea_row(' ', data->map->width);
		if (!data->map->minimap[i + data->map->height + 4])
			return (ft_freesplit(data->map->minimap), 1);
	}
	return (0);
}

int	crea_minimap(t_data *data)
{
	data->map->minimap = ft_calloc(data->map->height + 9, sizeof(char *));
	if (!data->map->minimap)
		return (1);
	if (init_minimap(data))
		return (1);
	return (0);
}
