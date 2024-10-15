/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:12:27 by etessier          #+#    #+#             */
/*   Updated: 2024/10/09 13:12:28 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	control_char_map(char *map1d)
{
	int	i;
	int player;

	i = ((player = -1));
	while (map1d[++i])
	{
		if (map1d[i] == '\n' && map1d[i + 1] == '\n')
			return (ft_putendl_fd(ERR_MAP_NL, 2), 1);
		if (map1d[i] == '0' || map1d[i] == '1' || map1d[i] == ' ' || \
			map1d[i] == '\n')
			continue ;
		if (map1d[i] == 'N' || map1d[i] == 'S' || map1d[i] == 'E' || \
			map1d[i] == 'W')
		{
			if (player == -1)
				player = 1;
			else
				return (ft_putendl_fd(ERR_MAP_PLAYER, 2), 1);
		}
		else
			return (ft_putendl_fd(ERR_CHAR_MAP, 2), 1);
	}
	if (player == -1)
		return (ft_putendl_fd(ERR_MAP_PLAYER, 2), 1);
	return (0);
}

static char	**crea_map_flood(size_t width, size_t height, t_data *data)
{
	size_t	i;
	size_t	j;

	data->map->map2d_copy = ft_calloc(height + 2, sizeof(char *));
	if (!data->map->map2d_copy)
		return (NULL);
	i = -1;
	while (++i <= height)
	{
		data->map->map2d_copy[i] = ft_calloc(width + 1, sizeof(char));
		if (!data->map->map2d_copy[i])
			return (ft_freesplit(data->map->map2d_copy), NULL);
		data->map->map2d_copy[i][0] = ' ';
		j = 0;
		if (i % height == 0)
			while (++j < width - 1)
				data->map->map2d_copy[i][j] = ' ';
		else
			while (data->map->map2d[i - 1][++j - 1])
				data->map->map2d_copy[i][j] = data->map->map2d[i - 1][j - 1];
		while (j < width)
			data->map->map2d_copy[i][j++] = ' ';
		data->map->map2d_copy[i][j] = '\0';
	}
	return (data->map->map2d_copy);
}

static void	flood_fill(char **map, int x, int y, t_data *data)
{
	map[x][y] = 'X';
	if (x > 0 && (map[x - 1][y] != ' ' && map[x - 1][y] != '1' \
			&& map[x - 1][y] != 'X'))
		return (ft_putendl_fd(ERR_MAP_OPEN_WALL, 2), (void)exit_pgm(data));
	if (y > 0 && (map[x][y - 1] != ' ' && map[x][y - 1] != '1' \
			&& map[x][y - 1] != 'X'))
		return (ft_putendl_fd(ERR_MAP_OPEN_WALL, 2), (void)exit_pgm(data));
	if (map[x + 1] && (map[x + 1][y] != ' ' && map[x + 1][y] != '1' \
			&& map[x + 1][y] != 'X'))
		return (ft_putendl_fd(ERR_MAP_OPEN_WALL, 2), (void)exit_pgm(data));
	if (map[x][y + 1] && (map[x][y + 1] != ' ' && map[x][y + 1] != '1' \
			&& map[x][y + 1] != 'X'))
		return (ft_putendl_fd(ERR_MAP_OPEN_WALL, 2), (void)exit_pgm(data));
	if (x > 0 && map[x - 1][y] == ' ')
		flood_fill(map, x - 1, y, data);
	if (y > 0 && map[x][y - 1] == ' ')
		flood_fill(map, x, y - 1, data);
	if (map[x + 1] && map[x + 1][y] == ' ')
		flood_fill(map, x + 1, y, data);
	if (map[x][y + 1] && map[x][y + 1] == ' ')
		flood_fill(map, x, y + 1, data);
}

static int	control_map_closed(t_data *data)
{
	size_t	width;
	size_t	height;

	width = 0;
	height = -1;
	while (data->map->map2d[++height])
	{
		if (ft_strlen(data->map->map2d[height]) > width)
			width = ft_strlen(data->map->map2d[height]);
	}
	data->map->height = height;
	data->map->width = width;
	height += 1;
	width += 2;
	data->map->map2d_copy = crea_map_flood(width, height, data);
	flood_fill(data->map->map2d_copy, 0, 0, data);
	return (0);
}

int	init_map(t_data *data)
{
	char	*map1d;

	map1d = load_map(data);
	if (control_char_map(map1d))
		return (free(map1d), 1);
	data->map->map2d = ft_split(map1d, '\n');
	free(map1d);
	if (!data->map->map2d)
		return (1);
	if (control_map_closed(data))
		return (1);
	find_player(data);
	printf("player x = %d\n", data->player.x);
	printf("player y = %d\n", data->player.y);
	return (0);
}
