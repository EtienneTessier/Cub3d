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

static void	free_textures(t_img *img)
{
	if (img->ceiling)
		free(img->ceiling);
	if (img->floor)
		free(img->floor);
	if (img->north)
		free(img->north);
	if (img->south)
		free(img->south);
	if (img->east)
		free(img->east);
	if (img->west)
		free(img->west);
	free(img);
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

void	free_data(t_data *data)
{
	if (data->img)
		free_textures(data->img);
	if (data->map)
		free_map(data->map);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data);
}

int	exit_pgm(t_data *data)
{
	if (data)
		free_data(data);
	exit (1);
}
