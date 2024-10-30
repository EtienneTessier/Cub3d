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

static void	swap_sprites(t_enemy *ennemis, int pos)
{
	t_enemy	enemy_tmp;

	enemy_tmp = ennemis[pos];
	ennemis[pos] = ennemis[pos + 1];
	ennemis[pos + 1] = enemy_tmp;
}

void	sort_sprites(t_enemy *ennemis, int sprites_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < sprites_count - 1)
	{
		j = 0;
		while (j < sprites_count - 1)
		{
			if (ennemis[j].distance < ennemis[j + 1].distance)
				swap_sprites(ennemis, j);
			j++;
		}
		i++;
	}
}
