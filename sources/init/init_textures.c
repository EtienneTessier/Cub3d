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

static int	init_texture_img(t_data *data, t_img *image, char *path)
{
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->txr->width,
			&data->txr->height);
	if (!image->img)
		return (1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
	return (0);
}

static int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	if (init_texture_img(data, &tmp, path))
		return (NULL);
	buffer = ft_calloc(1, sizeof * buffer * data->txr->width * \
			data->txr->height);
	if (!buffer)
		(free_data(data), exit(1));
	y = 0;
	while (y < data->txr->height)
	{
		x = 0;
		while (x < data->txr->width)
		{
			buffer[y * data->txr->width + x] \
				= tmp.addr[y * data->txr->width + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

static int	set_color(char *line)
{
	int		i;
	int		color;
	char	**colors;

	colors = ft_split(&line[skip_char(&line[1], ' ')], ',');
	if (!colors)
		return (0);
	i = -1;
	while (++i < 3)
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			return (ft_freesplit(colors), 0);
	color = rgb_to_hex(ft_atoi(colors[0]), ft_atoi(colors[1]), \
		ft_atoi(colors[0]));
	ft_freesplit(colors);
	return (color);
}

static int	set_textures(char *line, t_data *data, t_txr *txr)
{
	char	*texture_path;

	if (line[0] == 'C')
		return (data->txr->ceiling = set_color(line), 0);
	else if (line[0] == 'F')
		return (data->txr->floor = set_color(line), 0);
	texture_path = get_texture_path(&line[2]);
	if (!texture_path)
		return (1);
	if (line[0] == 'N')
		txr->north = xpm_to_img(data, texture_path);
	else if (line[0] == 'S')
		txr->south = xpm_to_img(data, texture_path);
	else if (line[0] == 'E')
		txr->east = xpm_to_img(data, texture_path);
	else if (line[0] == 'W')
		txr->west = xpm_to_img(data, texture_path);
	free(texture_path);
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
		if (!line)
			return (1);
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		i = skip_char(line, ' ');
		if (check_line(line, i, data->txr))
			return (free(line), 1);
		(set_textures(&line[i], data, data->txr), free(line));
		textures_init++;
	}
	return (check_textures(data->txr, data->map->fd));
}
