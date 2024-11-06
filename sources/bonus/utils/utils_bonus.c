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

#include "../../../includes/cub3d.h"

static int	is_bonus_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == '\n' || c == 'T' \
			|| c == 'B' || c == 'D')
		return (1);
	return (0);
}

int	control_char_map_bonus(char *map1d)
{
	int	i;
	int	player;

	i = ((player = -1));
	while (map1d[++i])
	{
		if (map1d[i] == '\n' && map1d[i + 1] == '\n')
			return (ft_putendl_fd(ERR_MAP_NL, 2), 1);
		if (is_bonus_char(map1d[i]))
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
