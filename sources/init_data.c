/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:47:58 by etessier          #+#    #+#             */
/*   Updated: 2024/10/09 12:47:59 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_data	*crea_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(1);
	data->height = 64;
	data->width = 64;
	data->map2d = NULL;
	data->mlx = NULL;
	data->win = NULL;
}

static t_img	*crea_img(t_data *data)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		(free(data), exit(1));
	img->ceiling = NULL;
	img->floor = NULL;
	img->north = NULL;
	img->south = NULL;
	img->east = NULL;
	img->west = NULL;
	return (img);
}

t_data	*init_data(char *map_path)
{
	t_data	*data;

	data = crea_data();
	data->img = crea_img(data);
	data->mlx = mlx_init(data);
	if (!data->mlx)
		return (free_data(data), NULL);
	if (init_textures(map_path, data))
		return (free_data(data), NULL);
	if (init_map(data))
		return (free_data(data), NULL);
}
