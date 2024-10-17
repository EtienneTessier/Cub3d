/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:09:29 by etessier          #+#    #+#             */
/*   Updated: 2024/10/09 15:09:30 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//	Controle si la ligne de parametre
static int	check_line(char *line, int i, t_txtr *txtr)
{
	int	type;

	(void)type;
	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		type = COLOR;
	else if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || \
			!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2)) \
			&& line[i + 2] == ' ')
		type = TEXTURE;
	else
		return (ft_putendl_fd(ERR_TEXTURE_FMT, 2), 1);
	if (line[i] == 'F' && txtr->floor == NULL)
		return (0);
	if (line[i] == 'C' && txtr->ceiling == NULL)
		return (0);
	if (line[i] == 'N' && txtr->north == NULL)
		return (0);
	if (line[i] == 'S' && txtr->south == NULL)
		return (0);
	if (line[i] == 'E' && txtr->east == NULL)
		return (0);
	if (line[i] == 'W' && txtr->west == NULL)
		return (0);
	return (ft_putendl_fd(ERR_TEXTURE_DOUBLE, 2), 1);
}

//	Recupere le chemin vers la texture (murs) -> Controle xpm ?
static char	*get_texture_path(char *line)
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

static int	*set_color(char *line)
{
	(void)line;
	return (ft_printf("set ceiling/floor\n"), NULL);
}

static int	set_textures(char *line, t_data *data, t_txtr *txtr)
{
	char	*texture_path;

	if (line[0] == 'C')
		return (data->txtr->ceiling = set_color(line), 0);
	else if (line[0] == 'F')
		return (data->txtr->floor = set_color(line), 0);
	texture_path = get_texture_path(&line[2]);
	if (!texture_path)
		return (1);
	// ft_printf("texture_path = %s\n", texture_path);
	if (line[0] == 'N')
		txtr->north = mlx_xpm_file_to_image(data->mlx, texture_path,
			&txtr->width, &txtr->height);
	else if (line[0] == 'S')
		txtr->south = mlx_xpm_file_to_image(data->mlx, texture_path,
			&txtr->width, &txtr->height);
	else if (line[0] == 'E')
		txtr->east = mlx_xpm_file_to_image(data->mlx, texture_path,
			&txtr->width, &txtr->height);
	else if (line[0] == 'W')
		txtr->west = mlx_xpm_file_to_image(data->mlx, texture_path,
			&txtr->width, &txtr->height);
	free(texture_path);
	return (0);
}

static int	check_textures(t_txtr *txtr)
{
	if (!txtr->east)
		return (ft_putendl_fd(ERR_TEXTURES_LOAD, 2), 1);
	if (!txtr->west)
		return (ft_putendl_fd(ERR_TEXTURES_LOAD, 2), 1);
	if (!txtr->north)
		return (ft_putendl_fd(ERR_TEXTURES_LOAD, 2), 1);
	if (!txtr->south)
		return (ft_putendl_fd(ERR_TEXTURES_LOAD, 2), 1);
	// if (!txtr->ceiling)
	// 	return (ft_putendl_fd(ERR_TEXTURES_LOAD, 2), 1);
	// if (!txtr->floor)
	// 	return (ft_putendl_fd(ERR_TEXTURES_LOAD, 2), 1);
	return (0);
}

int	init_textures(char *map_path, t_data *data)
{
	int		i;
	int		textures_init;
	char	*line;

	data->map->fd = open(map_path, O_RDONLY);
	if (data->map->fd == -1)
		return (ft_putendl_fd(ERR_MAP_OPEN, 2), 1);
	textures_init = 0;
	while (textures_init < 6)
	{
		line = get_next_line(data->map->fd);
		if (!line || line[0] == '\0')
			return (1);
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		i = skip_char(line, ' ');
		if (check_line(line, i, data->txtr))
			return (free(line), 1);
		(set_textures(&line[i], data, data->txtr), free(line));
		textures_init++;
	}
	return (check_textures(data->txtr));
}
