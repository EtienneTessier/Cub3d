/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:56:59 by etessier          #+#    #+#             */
/*   Updated: 2024/10/11 14:57:00 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map_2d(char **map2d)
{
	int	i;
	int	j;

	i = -1;
	while (map2d[++i])
	{
		j = -1;
		while (map2d[i][++j])
			ft_printf("%c", map2d[i][j]);
		ft_printf("\n");
	}
}

// side == 1 && dir_y > 0 --> S
// side == 1 && dir_y < 0 --> N
// side == 0 && dir_x > 0 --> E
// side == 0 && dir_x < 0 --> W
void	load_color(t_ray *ray, t_data *data)
{
	if (ray->side == 1)
	{
		if (ray->ray_dir_y > 0)
			data->txr->color = GRI_PIXEL;
		else
			data->txr->color = ORA_PIXEL;
	}
	else
	{
		if (ray->ray_dir_x > 0)
			data->txr->color = WHI_PIXEL;
		else
			data->txr->color = GRE_PIXEL;
	}
	load_col(ray, data);
}

void	print_sprites_data(t_data *data)
{
	int	i;

	ft_printf("nb sprites : %d\n", data->ennemis_count);
	i = 0;
	while (i < data->ennemis_count)
	{
		ft_printf("i = %d\n", i);
		printf("data->sprites[i].x = %f\n", data->ennemis[i].x);
		printf("data->sprites[i].y = %f\n", data->ennemis[i].y);
		i++;
	}
}
