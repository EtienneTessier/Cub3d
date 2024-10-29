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

void	swap_sprites(double *distance, int pos)
{
	double	distance_tmp;

	distance_tmp = distance[pos];
	distance[pos] = distance[pos + 1];
	distance[pos + 1] = distance_tmp;
}

void	sort_sprites(double *distance, int sprites_count)
{
	int	i;
	int j;

	i = 0;
	while (i < sprites_count - 1)
	{
		j = i;
		while (j < sprites_count - 1)
		{
			if (distance[j] < distance[j + 1])
				swap_sprites(distance, j);
			j++;
		}
		i++;
	}
}

