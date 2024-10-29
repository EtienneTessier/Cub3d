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

static int	init_minimap(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < 4)
	{
		data->map->minimap[i] = crea_row(' ', data->map->width);
		if (!data->map->minimap[i])
			return (ft_freesplit(data->map->minimap), 1);
	}
	i = -1;
	while (++i < data->map->height)
	{
		data->map->minimap[i + 4] = ft_strdup(data->map->map2d[i]);
		if (!data->map->minimap[i + 4])
			return (ft_freesplit(data->map->minimap), 1);
	}
	i = -1;
	while (++i < 4)
	{
		data->map->minimap[i + data->map->height + 4] = crea_row(' ', \
			data->map->width);
		if (!data->map->minimap[i + data->map->height + 4])
			return (ft_freesplit(data->map->minimap), 1);
	}
	return (0);
}

static int	crea_minimap(t_data *data)
{
	data->map->minimap = ft_calloc(data->map->height + 9, sizeof(char *));
	if (!data->map->minimap)
		return (1);
	if (init_minimap(data))
		return (1);
	return (0);
}

int	init_bonus(t_data *data)
{
	if (init_textures_bonus(data))
		return (1);
	if (init_ennemis(data))
		return (1);
	if (crea_minimap(data))
		return (1);
	return (0);
}
