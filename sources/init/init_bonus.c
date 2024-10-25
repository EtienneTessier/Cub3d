/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:18:23 by etienne           #+#    #+#             */
/*   Updated: 2024/10/25 10:18:24 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	init_texture_img(t_data *data, t_img *image, char *path)
{
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->txr->sky_width,
			&data->txr->sky_height);
	if (!image->img)
		return (1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
	return (0);
}

static int	*sky_xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	if (init_texture_img(data, &tmp, path))
		return (NULL);
	buffer = ft_calloc(1, sizeof(int) * SCR_WIDTH * SCR_HEIGHT);
	if (!buffer)
		exit_pgm(data);
	y = 0;
	while (y < SCR_HEIGHT)
	{
		x = 0;
		while (x < SCR_WIDTH)
		{
			buffer[y * SCR_WIDTH + x] \
				= tmp.addr[y * SCR_WIDTH + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

static int	get_ennemis(t_data *data)
{
	int	y;
	int	x;
	int	enemy;

	y = ((enemy = 0));
	while (data->map->map2d[y])
	{
		x = 0;
		while (data->map->map2d[y][x])
		{
			if (data->map->map2d[y][x] == 'T')
			{
				data->ennemis[enemy].alive = 1;
				data->ennemis[enemy].x = x;
				data->ennemis[enemy].y = y;
				data->map->map2d[y][x] = '0';
				enemy++;
			}
			x++;
		}
		y++;
	}
	ft_printf("ennemis : %d\n", enemy);
	if (enemy > 5)
		return (ft_putendl_fd(ERR_ENE_COUNT, 2), 1);
	return (0);
}

static int	init_ennemis(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->ennemis[i].alive = 0;
		i++;
	}
	return (get_ennemis(data));
}

int		init_bonus(t_data *data)
{
	data->txr->sky = sky_xpm_to_img(data, SKY_PATH);
	if (!data->txr->sky)
		return (1);
	if (init_ennemis(data))
		return (1);
	if (crea_minimap(data))
		return (1);
	return (0);
}
