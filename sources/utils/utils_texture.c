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
int	check_line(char *line, int i, t_txr *txtr)
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
	ft_printf("line = %s\n", line);
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
