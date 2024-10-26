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

static int	count_sprites(char **map)
{
	int	nb_sprites;
	int	y;
	int	x;

	nb_sprites = ((y = 0));
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'B' || map[y][x] == 'T')
				nb_sprites++;
			x++;
		}
		y++;
	}
	return (nb_sprites);
}

static int	set_sprites(t_data *data)
{
	int	i;
	int	y;
	int	x;

	i = ((y = -1));
	while (data->map->map2d[++y])
	{
		x = -1;
		while (data->map->map2d[y][++x])
		{
			if (data->map->map2d[y][x] == 'B' || data->map->map2d[y][x] == 'T')
			{
				i++;
				data->sprites[i].x = x + 0.5;
				data->sprites[i].y = y + 0.5;
				if (data->map->map2d[y][x] == 'T')
					data->sprites[i].txr = data->txr->pillar;
				else
					data->sprites[i].txr = data->txr->barrel;
				data->map->map2d[y][x] = '0';
			}
		}
	}
	return (0);
}

static int	init_texture_img_sprite(t_data *data, t_img *image, char *path)
{
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->txr->sprite_width,
			&data->txr->sprite_height);
	if (!image->img)
		return (1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
	return (0);
}

static int	*sprite_xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	if (init_texture_img_sprite(data, &tmp, path))
		return (NULL);
	buffer = ft_calloc(1, sizeof(int) * SPRITE_SIZE * SPRITE_SIZE);
	if (!buffer)
		exit_pgm(data);
	y = 0;
	while (y < SPRITE_SIZE)
	{
		x = 0;
		while (x < SPRITE_SIZE)
		{
			buffer[y * SPRITE_SIZE + x] \
				= tmp.addr[y * SPRITE_SIZE + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

static void	print_sprites_data(t_data *data)
{
	int	i;

	ft_printf("nb sprites : %d\n", data->sprites_count);
	i = 0;
	while (i < data->sprites_count)
	{
		ft_printf("i = %d\n", i);
		printf("data->sprites[i].x = %f\n", data->sprites[i].x);
		printf("data->sprites[i].y = %f\n", data->sprites[i].y);
		i++;
	}
}

int	init_sprites(t_data *data)
{
	data->sprites_count = count_sprites(data->map->map2d);
	if (data->sprites_count == 0)
		return (0);
	data->sprites = ft_calloc(data->sprites_count, sizeof(t_sprites));
	if (!data->sprites)
		return (1);
	data->txr->barrel = sprite_xpm_to_img(data, BARREL_PATH);
	if (!data->txr->barrel)
		return (1);
	data->txr->pillar = sprite_xpm_to_img(data, PILLAR_PATH);
	if (!data->txr->pillar)
		return (1);
	if (set_sprites(data))
		return (1);
	print_sprites_data(data);
	return (0);
}
