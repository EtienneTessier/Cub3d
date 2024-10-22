/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:31:45 by etienne           #+#    #+#             */
/*   Updated: 2024/10/20 10:31:46 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//	Controle si la ligne de parametre
int	check_line(char *line, int i, t_txr *txr)
{
	if (line[i] == ' ' || line[i] == '0' || line[i] == '1')
		return (ft_putendl_fd(ERR_LINE_FMT, 2), 1);
	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] != ' ')
		return (ft_putendl_fd(ERR_LINE_COLOR_FMT, 2), 1);
	else if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || \
			!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2)) \
			&& line[i + 2] != ' ')
		return (ft_putendl_fd(ERR_LINE_TEXTURE_FMT, 2), 1);
	if (line[i] == 'F' && txr->floor == -1)
		return (0);
	if (line[i] == 'C' && txr->ceiling == -1)
		return (0);
	if (line[i] == 'N' && txr->north == NULL)
		return (0);
	if (line[i] == 'S' && txr->south == NULL)
		return (0);
	if (line[i] == 'E' && txr->east == NULL)
		return (0);
	if (line[i] == 'W' && txr->west == NULL)
		return (0);
	return (ft_putendl_fd(ERR_TEXTURE_DOUBLE, 2), 1);
}

char	*get_texture_path(char *line)
{
	int		i;
	int		j;
	int		size;
	char	*texture_path;

	size = 0;
	j = skip_char(line, ' ');
	line += j;
	while (line[size] && ft_isprint(line[size]) && line[size] != ' ')
		size++;
	texture_path = ft_calloc(size + 1, sizeof(char));
	if (!texture_path)
		return (NULL);
	i = 0;
	while (line[i] && ft_isprint(line[i]) && line[i] != ' ')
	{
		texture_path[i] = line [i];
		i++;
	}
	texture_path[i] = '\0';
	return (texture_path);
}

void	close_gnl(int fd)
{
	char	*str;

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		free(str);
	}
}

int	check_textures(t_txr *txr, int map_fd)
{
	if (!txr->east)
		return (ft_putendl_fd(ERR_TEXTURES_LOAD_E, 2), close_gnl(map_fd), 1);
	if (!txr->west)
		return (ft_putendl_fd(ERR_TEXTURES_LOAD_W, 2), close_gnl(map_fd), 1);
	if (!txr->north)
		return (ft_putendl_fd(ERR_TEXTURES_LOAD_N, 2), close_gnl(map_fd), 1);
	if (!txr->south)
		return (ft_putendl_fd(ERR_TEXTURES_LOAD_S, 2), close_gnl(map_fd), 1);
	return (0);
}
