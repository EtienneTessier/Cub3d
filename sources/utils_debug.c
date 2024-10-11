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
