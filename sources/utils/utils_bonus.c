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

#include "../../includes/cub3d.h"

int	control_char_map_bonus(char *map1d)
{
	int	i;
	int	player;

	i = ((player = -1));
	while (map1d[++i])
	{
		if (map1d[i] == '\n' && map1d[i + 1] == '\n')
			return (ft_putendl_fd(ERR_MAP_NL, 2), 1);
		if (map1d[i] == '0' || map1d[i] == '1' || map1d[i] == ' ' || \
			map1d[i] == '\n' || map1d[i] == 'T')
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
