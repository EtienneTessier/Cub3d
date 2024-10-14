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
static int	check_line(char *line, int i, t_img *img)
{
	int	type;

	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		type = COLOR;
	else if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || \
			!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2)) \
			&& line[i + 2] == ' ')
		type = TEXTURE;
	else
		return (ft_putendl_fd(ERR_TEXTURE_FMT, 2), 1);
	if (line[i] == 'F' && img->floor == NULL)
		return (0);
	if (line[i] == 'C' && img->ceiling == NULL)
		return (0);
	if (line[i] == 'N' && img->north == NULL)
		return (0);
	if (line[i] == 'S' && img->south == NULL)
		return (0);
	if (line[i] == 'E' && img->east == NULL)
		return (0);
	if (line[i] == 'W' && img->west == NULL)
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
	return (ft_printf("set ceiling/floor\n"), 0);
}

static int	set_textures(char *line, t_data *data, t_img *img)
{
	char	*texture_path;

	(void)data;
	(void)img;
	if (line[0] == 'C')
		return (data->img->ceiling = set_color(line), 0);
	else if (line[0] == 'F')
		return (data->img->floor = set_color(line), 0);
	texture_path = get_texture_path(&line[2]);
	if (!texture_path)
		return (1);
	ft_printf("texture_path = %s\n", texture_path);
	if (line[0] == 'N')
		ft_printf("set north\n");
		// img->north = mlx_xpm_file_to_image(data->mlx, texture_path,
		// 	&img->width, &img->height);
	else if (line[0] == 'S')
		ft_printf("set south\n");
		// img->south = mlx_xpm_file_to_image(data->mlx, texture_path,
		// 	&img->width, &img->height);
	else if (line[0] == 'E')
		ft_printf("set east\n");
		// img->east = mlx_xpm_file_to_image(data->mlx, texture_path,
		// 	&img->width, &img->height);
	else if (line[0] == 'W')
		ft_printf("set west\n");
		// img->west = mlx_xpm_file_to_image(data->mlx, texture_path,
		// 	&img->width, &img->height);
	free(texture_path);
	return (0);
}

int	init_textures(char *map_path, t_data *data)
{
	int		i;
	int		textures_init;
	char	*line;

	data->map_fd = open(map_path, O_RDONLY);
	if (data->map_fd == -1)
		return (ft_putendl_fd(ERR_MAP_OPEN, 2), 1);
	textures_init = 0;
	while (textures_init < 6)
	{
		line = get_next_line(data->map_fd);
		if (!line || line[0] == '\0')
			return (1);
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		i = skip_char(line, ' ');
		if (check_line(line, i, data->img))
			return (free(line), 1);
		(set_textures(&line[i], data, data->img), free(line));
		textures_init++;
	}
	return (0);
}
