/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:46:09 by etessier          #+#    #+#             */
/*   Updated: 2024/10/22 10:46:10 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	control_color_line(char **colors)
{
	int	i;
	int	j;

	i = -1;
	while (colors[++i])
	{
		j = -1;
		while (colors[i][++j])
		{
			if (colors[i][j] == '\n')
				break ;
			if (colors[i][j] < '0' || colors[i][j] > '9')
				return (ft_putendl_fd(ERR_COLOR_CHA, 2), 1);
		}
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			return (ft_putendl_fd(ERR_COLOR_VAL, 2), 1);
	}
	if (i != 3)
		return (ft_putendl_fd(ERR_COLOR_FMT, 2), 1);
	return (0);
}

unsigned int	rgb_to_hex(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}

int	set_color(char *line)
{
	int		i;
	int		color;
	char	**colors;

	i = skip_char(&line[1], ' ') + 1;
	colors = ft_split(&line[i], ',');
	if (!colors)
		return (-1);
	if (control_color_line(colors))
		return (ft_freesplit(colors), -1);
	color = rgb_to_hex(ft_atoi(colors[0]), ft_atoi(colors[1]), \
		ft_atoi(colors[2]));
	ft_freesplit(colors);
	return (color);
}
