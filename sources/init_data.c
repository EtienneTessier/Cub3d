/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:47:58 by etessier          #+#    #+#             */
/*   Updated: 2024/10/09 12:47:59 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_data	*crea_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(1);
	data->map = NULL;
	data->txtr = NULL;
	data->mlx = NULL;
	data->win = NULL;
	return (data);
}

static t_txtr	*crea_txtr(t_data *data)
{
	t_txtr	*txtr;

	txtr = ft_calloc(1, sizeof(t_txtr));
	if (!txtr)
		(free(data), exit(1));
	txtr->ceiling = NULL;
	txtr->floor = NULL;
	txtr->north = NULL;
	txtr->south = NULL;
	txtr->east = NULL;
	txtr->west = NULL;
	return (txtr);
}

static t_map	*crea_map(t_data *data)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		(free(data), exit(1));
	map->map2d = NULL;
	map->map2d_copy = NULL;
	map->fd = -1;
	return (map);
}

t_data	*init_data(char *map_path)
{
	t_data	*data;

	data = crea_data();
	data->txtr = crea_txtr(data);
	data->map = crea_map(data);
	data->mlx = mlx_init(data);
	if (!data->mlx)
		return (free_data(data), NULL);
	if (init_textures(map_path, data))
		return (free_data(data), NULL);
	if (init_map(data))
		return (free_data(data), NULL);
	return (data);
}
