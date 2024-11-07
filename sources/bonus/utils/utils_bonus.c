/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:47:16 by etienne           #+#    #+#             */
/*   Updated: 2024/10/25 17:47:17 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	is_bonus_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == '\n' || c == 'T' \
			|| c == 'B' || c == 'D')
		return (1);
	return (0);
}

int	control_char_map_bonus(char *map1d)
{
	int	i;
	int	player;

	i = ((player = -1));
	while (map1d[++i])
	{
		if (map1d[i] == '\n' && map1d[i + 1] == '\n')
			return (ft_putendl_fd(ERR_MAP_NL, 2), 1);
		if (is_bonus_char(map1d[i]))
			continue ;
		if (map1d[i] == 'N' || map1d[i] == 'S' || map1d[i] == 'E' || \
			map1d[i] == 'W')
		{
			if (player == -1)
				player = 1;
			else
				return (ft_putendl_fd(ERR_MAP_PLAYER, 2), 1);
		}
		else
			return (ft_putendl_fd(ERR_MAP_CHAR, 2), 1);
	}
	if (player == -1)
		return (ft_putendl_fd(ERR_MAP_PLAYER, 2), 1);
	return (0);
}

static int	bonus_init_texture_img(t_data *data, t_img *image, char *path)
{
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->txr->bonus_width,
			&data->txr->bonus_height);
	if (!image->img)
		return (1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
	return (0);
}

int	*bonus_xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	if (bonus_init_texture_img(data, &tmp, path))
		return (NULL);
	buffer = ft_calloc(1, sizeof * buffer * data->txr->bonus_width * \
			data->txr->bonus_height);
	if (!buffer)
		exit_pgm(data, 1);
	y = 0;
	while (y < data->txr->bonus_height)
	{
		x = 0;
		while (x < data->txr->bonus_width)
		{
			buffer[y * data->txr->bonus_width + x] \
				= tmp.addr[y * data->txr->bonus_width + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}
