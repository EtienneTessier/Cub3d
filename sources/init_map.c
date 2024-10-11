/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:12:27 by etessier          #+#    #+#             */
/*   Updated: 2024/10/09 13:12:28 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*load_map(t_data *data)
{
	char	*str;
	char	*map1d;

	while (1)
	{
		map1d = get_next_line(data->map_fd);
		if (!map1d || map1d[0] == '\0')
			return (map1d);
		if (map1d[0] != '\n')
			break ;
		free(map1d);
	}
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str || str[0] == '\0')
			return (map1d);
		map1d = ft_join(map1d, str, ft_strlen(str));
		free(str);
		if (!map1d)
			return (NULL);
	}
}

static int	control_char_map(char *map1d)
{
	int	i;

	i = -1;
	while (map1d[++i])
	{
		if (map1d[i] == '\n' && map1d[i + 1] == '\n')
			return (ft_putendl_fd(ERR_MAP_NL, 2), 1);
		if (map1d[i] == '0' || map1d[i] == '1' || map1d[i] == ' ' || \
			map1d[i] == 'N' || map1d[i] == 'S' || map1d[i] == 'E' || \
			map1d[i] == 'W' || map1d[i] == '\n')
			continue ;
		else
			return (ft_putendl_fd(ERR_CHAR_MAP, 2), 1);
	}
	return (0);
}

int	init_map(t_data *data)
{
	char	*map1d;

	map1d = load_map(data);
	ft_printf("map :\n%s", map1d);
	if (control_char_map(map1d))
		return (free(map1d), 1);
	// -> chargement de la map 2D
	// -> control map closed
	(void)data;
	free(map1d);
	return (0);
}
