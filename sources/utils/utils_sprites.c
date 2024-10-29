/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:36:08 by etessier          #+#    #+#             */
/*   Updated: 2024/10/28 09:36:09 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	swap_sprites(double *distance, t_enemy *ennemis, int pos)
{
	double	distance_tmp;
	t_enemy	enemy_tmp;

	distance_tmp = distance[pos];
	distance[pos] = distance[pos + 1];
	distance[pos + 1] = distance_tmp;
	enemy_tmp = ennemis[pos];
	ennemis[pos] = ennemis[pos + 1];
	ennemis[pos + 1] = enemy_tmp;
}

void	sort_sprites(double *distance, t_enemy *ennemis, int sprites_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < sprites_count - 1)
	{
		j = 0;
		while (j < sprites_count - 1)
		{
			// printf("j = %d\n", j);
			// printf("distance[j] = %f, distance[j + 1] = %f\n", distance[j], distance[j + 1]);
			if (distance[j] < distance[j + 1])
				swap_sprites(distance, ennemis, j);
			j++;
		}
		i++;
	}
}
