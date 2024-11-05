/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:26:26 by etienne           #+#    #+#             */
/*   Updated: 2024/10/25 18:26:27 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	init_texture_img_sky(t_data *data, t_img *image, char *path)
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

	if (init_texture_img_sky(data, &tmp, path))
		return (NULL);
	buffer = ft_calloc(1, sizeof(int) * SCR_WIDTH * SCR_HEIGHT);
	if (!buffer)
		exit_pgm(data, 1);
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

static int	init_texture_img_face(t_data *data, t_img *image, char *path)
{
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->txr->face_width,
			&data->txr->face_height);
	if (!image->img)
		return (1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
	return (0);
}

static int	*face_xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	if (init_texture_img_face(data, &tmp, path))
		return (NULL);
	buffer = ft_calloc(1, sizeof(int) * FACE_SIZE * FACE_SIZE);
	if (!buffer)
		exit_pgm(data, 1);
	y = 0;
	while (y < FACE_SIZE)
	{
		x = 0;
		while (x < FACE_SIZE)
		{
			buffer[y * FACE_SIZE + x] \
				= tmp.addr[y * FACE_SIZE + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

int	init_textures_bonus(t_data *data)
{
	data->txr->sky = sky_xpm_to_img(data, SKY_PATH);
	if (!data->txr->sky)
		return (1);
	data->txr->weapon = sky_xpm_to_img(data, WEAPON_PATH);
	if (!data->txr->weapon)
		return (1);
	data->txr->shoot = sky_xpm_to_img(data, SHOOT_PATH);
	if (!data->txr->shoot)
		return (1);
	data->txr->terro = face_xpm_to_img(data, TERRO_PATH);
	if (!data->txr->terro)
		return (1);
	data->txr->terro_dead = face_xpm_to_img(data, TERRO_D_PATH);
	if (!data->txr->terro)
		return (1);
	data->txr->ct = face_xpm_to_img(data, CT_PATH);
	if (!data->txr->ct)
		return (1);
	return (0);
}
