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

static int	init_texture_img_barrel(t_data *data, t_img *image, char *path)
{
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->txr->barrel_width,
			&data->txr->barrel_height);
	if (!image->img)
		return (1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
	return (0);
}

static int	*barrel_xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	if (init_texture_img_barrel(data, &tmp, path))
		return (NULL);
	buffer = ft_calloc(1, sizeof(int) * BARREL_SIZE * BARREL_SIZE);
	if (!buffer)
		exit_pgm(data);
	y = 0;
	while (y < BARREL_SIZE)
	{
		x = 0;
		while (x < BARREL_SIZE)
		{
			buffer[y * BARREL_SIZE + x] \
				= tmp.addr[y * BARREL_SIZE + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

int	init_sprites(t_data *data)
{
	data->txr->barrel = barrel_xpm_to_img(data, BARREL_PATH);
	if (!data->txr->barrel)
		return (1);
	return (0);
}
