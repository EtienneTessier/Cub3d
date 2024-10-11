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

void	free_data(t_data *data)
{
	if (data->img)
		free_textures(data->img);
	if (data->map2d_copy)
		ft_freesplit(data->map2d_copy);
	if (data->map2d)
		ft_freesplit(data->map2d);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data)
		free(data);
}

void	exit_pgm(t_data *data)
{
	if (data)
		free_data(data);
	exit (1);
}
