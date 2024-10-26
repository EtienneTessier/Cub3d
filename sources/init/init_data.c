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
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->map = NULL;
	data->txr = NULL;
	data->sprites = NULL;
	data->ennemis_count = 0;
	data->sprites_count = 0;
	return (data);
}

static t_txr	*crea_txr(t_data *data)
{
	t_txr	*txr;

	txr = ft_calloc(1, sizeof(t_txr));
	if (!txr)
		exit_pgm(data);
	txr->ceiling = -1;
	txr->floor = -1;
	txr->north = NULL;
	txr->south = NULL;
	txr->east = NULL;
	txr->west = NULL;
	txr->sky = NULL;
	return (txr);
}

static t_map	*crea_map(t_data *data)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_pgm(data);
	map->map2d = NULL;
	map->map2d_copy = NULL;
	map->minimap = NULL;
	map->fd = -1;
	return (map);
}

static t_img	*crea_img(t_data *data)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		exit_pgm(data);
	img->addr = NULL;
	img->img = NULL;
	return (img);
}

t_data	*init_data(char *map_path)
{
	t_data	*data;

	data = crea_data();
	data->map = crea_map(data);
	data->img = crea_img(data);
	data->mlx = mlx_init(data);
	if (!data->mlx)
		return (free_data(data), NULL);
	data->txr = crea_txr(data);
	if (init_textures(map_path, data))
		return (free_data(data), NULL);
	if (init_map(data))
		return (free_data(data), NULL);
	if (BONUS)
		if (init_bonus(data))
			return (free_data(data), NULL);
	data->img->img = mlx_new_image(data->mlx, SCR_WIDTH, SCR_HEIGHT);
	data->img->addr = (int *)mlx_get_data_addr(data->img->img, &data->img->bpp, \
		&data->img->line_length, &data->img->endian);
	data->win = mlx_new_window(data->mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");
	return (data);
}
