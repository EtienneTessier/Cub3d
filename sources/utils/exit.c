/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:15:36 by etessier          #+#    #+#             */
/*   Updated: 2024/10/09 15:15:37 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_textures(t_txr *txr)
{
	if (txr->north)
		free(txr->north);
	if (txr->south)
		free(txr->south);
	if (txr->east)
		free(txr->east);
	if (txr->west)
		free(txr->west);
	if (txr->sky)
		free(txr->sky);
	if (txr->weapon)
		free(txr->weapon);
	if (txr->terro)
		free(txr->terro);
	if (txr->terro_dead)
		free(txr->terro_dead);
	if (txr->ct)
		free(txr->ct);
	if (txr->far)
		free(txr->far);
	if (txr->close)
		free(txr->close);
	if (txr->dead)
		free(txr->dead);
	free(txr);
}

static void	free_map(t_map *map)
{
	if (map->map2d_copy)
		ft_freesplit(map->map2d_copy);
	if (map->map2d)
		ft_freesplit(map->map2d);
	if (map->minimap)
		ft_freesplit(map->minimap);
	if (map->fd > 0)
		close(map->fd);
	free(map);
}

static void	free_img(void *mlx, t_img *img)
{
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	free(img);
}

void	free_data(t_data *data)
{
	if (data->txr)
	{
		if (data->txr->shoot)
			free(data->txr->shoot);
		if (data->txr->floor_txr)
			free(data->txr->floor_txr);
		if (data->txr->door)
			free(data->txr->door);
		free_textures(data->txr);
	}
	if (data->map)
		free_map(data->map);
	if (data->img)
		free_img(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	exit_pgm(t_data *data, int exit_code)
{
	if (data)
		free_data(data);
	exit (exit_code);
}
