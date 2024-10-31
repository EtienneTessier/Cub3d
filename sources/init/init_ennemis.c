/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_spirtes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 08:07:46 by etienne           #+#    #+#             */
/*   Updated: 2024/10/26 08:07:47 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_ennemis(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map->map2d[y])
	{
		x = 0;
		while (data->map->map2d[y][x])
		{
			if (data->map->map2d[y][x] == 'T')
			{
				if (data->ennemis_count == 5)
					return (ft_putendl_fd(ERR_ENE_COUNT, 2), 1);
				data->ennemis[data->ennemis_count].id = data->ennemis_count;
				data->ennemis[data->ennemis_count].alive = 1;
				data->ennemis[data->ennemis_count].x = x + 0.5;
				data->ennemis[data->ennemis_count].y = y + 0.5;
				data->map->map2d[y][x] = '0';
				data->ennemis_count++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	init_texture_img_ben(t_data *data, t_img *image, char *path)
{
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->txr->ben_width,
			&data->txr->ben_height);
	if (!image->img)
		return (1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
	return (0);
}

static int	*ben_xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	if (init_texture_img_ben(data, &tmp, path))
		return (NULL);
	buffer = ft_calloc(1, sizeof(int) * BEN_HEIGHT * BEN_WIDTH);
	if (!buffer)
		exit_pgm(data, 1);
	y = 0;
	while (y < BEN_WIDTH)
	{
		x = 0;
		while (x < BEN_HEIGHT)
		{
			buffer[y * BEN_WIDTH + x] \
				= tmp.addr[y * BEN_WIDTH + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

int	init_ennemis(t_data *data)
{
	int	i;

	data->ennemis_count = 0;
	i = 0;
	while (i < 5)
	{
		data->ennemis[i].alive = 0;
		i++;
	}
	if (get_ennemis(data))
		return (1);
	data->txr->right = ben_xpm_to_img(data, RIGHT_PATH);
	if (!data->txr->right)
		return (ft_putendl_fd(ERR_ENE_LOAD, 2), 1);
	data->txr->left = ben_xpm_to_img(data, LEFT_PATH);
	if (!data->txr->left)
		return (ft_putendl_fd(ERR_ENE_LOAD, 2), 1);
	data->txr->dead = ben_xpm_to_img(data, DEAD_PATH);
	if (!data->txr->dead)
		return (ft_putendl_fd(ERR_ENE_LOAD, 2), 1);
	return (0);
}
