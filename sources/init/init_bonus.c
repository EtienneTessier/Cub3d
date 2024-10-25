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
				data->ennemis[data->ennemis_count].alive = 1;
				data->ennemis[data->ennemis_count].x = x;
				data->ennemis[data->ennemis_count].y = y;
				data->map->map2d[y][x] = '0';
				data->ennemis_count++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	init_ennemis(t_data *data)
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
	return (0);
}

int		init_bonus(t_data *data)
{
	data->txr->sky = sky_xpm_to_img(data, SKY_PATH);
	if (!data->txr->sky)
		return (1);
	data->txr->terro = face_xpm_to_img(data, TERRO_PATH);
	if (!data->txr->terro)
		return (1);
	data->txr->ct = face_xpm_to_img(data, CT_PATH);
	if (!data->txr->ct)
		return (1);
	if (init_ennemis(data))
		return (1);
	if (crea_minimap(data))
		return (1);
	return (0);
}
