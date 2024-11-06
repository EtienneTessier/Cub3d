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

#include "../../../includes/cub3d.h"

static t_txr	*crea_txr(t_data *data)
{
	t_txr	*txr;

	txr = ft_calloc(1, sizeof(t_txr));
	if (!txr)
		exit_pgm(data, 1);
	txr->ceiling = -1;
	txr->floor = -1;
	return (txr);
}

static t_map	*crea_map(t_data *data)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_pgm(data, 1);
	map->fd = -1;
	return (map);
}

static t_img	*crea_img(t_data *data)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		exit_pgm(data, 1);
	return (img);
}

int	init_data(t_data *data, char *map_path)
{
	ft_memset(data, 0, sizeof(t_data));
	data->map = crea_map(data);
	data->img = crea_img(data);
	data->mlx = mlx_init(data);
	if (!data->mlx)
		return (free_data(data), 1);
	data->txr = crea_txr(data);
	if (init_textures(map_path, data) == 1)
		return (free_data(data), 1);
	if (init_map(data) == 1)
		return (free_data(data), 1);
	if (init_bonus(data) == 1)
		return (free_data(data), 1);
	data->img->img = mlx_new_image(data->mlx, SCR_WIDTH, SCR_HEIGHT);
	data->img->addr = (int *)mlx_get_data_addr(data->img->img, &data->img->bpp, \
		&data->img->line_length, &data->img->endian);
	data->win = mlx_new_window(data->mlx, SCR_WIDTH, SCR_HEIGHT, GAME_NAME_B);
	return (0);
}
