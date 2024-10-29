/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:13:21 by etienne           #+#    #+#             */
/*   Updated: 2024/10/25 18:13:22 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	print_terro(int i, t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < FACE_SIZE)
	{
		x = -1;
		if (data->ennemis[i].alive)
			while (++x < FACE_SIZE)
				my_mlx_pixel_put(data->img, SCR_WIDTH / 1.75 + \
					data->ennemis[i].id * (FACE_SIZE + 5) + x, y + 5, \
					data->txr->terro[y * FACE_SIZE + x]);
		else
			while (++x < FACE_SIZE)
				my_mlx_pixel_put(data->img, SCR_WIDTH / 1.75 + \
					data->ennemis[i].id * (FACE_SIZE + 5) + x, y + 5, \
					data->txr->terro_dead[y * FACE_SIZE + x]);
	}
}

static void	print_ct(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < FACE_SIZE)
	{
		x = -1;
		while (++x < FACE_SIZE)
		{
			my_mlx_pixel_put(data->img, SCR_WIDTH / 2.5 + x, \
				y + 5, data->txr->ct[y * FACE_SIZE + x]);
		}
	}
}

void	print_faces(t_data *data)
{
	int	i;

	if (data->ennemis_count == 0)
		return ;
	i = -1;
	while (++i < data->ennemis_count)
		print_terro(i, data);
	print_ct(data);
}
