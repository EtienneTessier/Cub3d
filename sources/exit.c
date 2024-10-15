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

static void	free_textures(t_txtr *txtr)
{
	if (txtr->ceiling)
		free(txtr->ceiling);
	if (txtr->floor)
		free(txtr->floor);
	if (txtr->north)
		free(txtr->north);
	if (txtr->south)
		free(txtr->south);
	if (txtr->east)
		free(txtr->east);
	if (txtr->west)
		free(txtr->west);
	free(txtr);
}

static void	free_map(t_map *map)
{
	if (map->map2d_copy)
		ft_freesplit(map->map2d_copy);
	if (map->map2d)
		ft_freesplit(map->map2d);
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
	if (data->txtr)
		free_textures(data->txtr);
	if (data->map)
		free_map(data->map);
	if (data->img)
		free_img(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		(mlx_destroy_display(data->mlx), free(data->mlx));
	free(data);
}

int	exit_pgm(t_data *data)
{
	if (data)
		free_data(data);
	exit (1);
}
