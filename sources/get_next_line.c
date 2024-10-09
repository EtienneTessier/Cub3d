/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:49:42 by etessier          #+#    #+#             */
/*   Updated: 2024/06/05 14:53:42 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*ft_join(char *s1, char *s2, int nb_read)
{
	int		i;
	int		j;
	char	*joined;

	if (!s2)
		return (s1);
	joined = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && j < nb_read)
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	free (s1);
	return (joined);
}

static char	*ft_read(int fd, char *save)
{
	int		i;
	int		nb_read;
	char	*buffer;

	nb_read = -1;
	buffer = ft_calloc (sizeof(char), 2);
	if (!buffer)
		return (free(save), NULL);
	while (nb_read != 0)
	{
		nb_read = read (fd, buffer, 1);
		if (nb_read == -1)
			return (free(save), free(buffer), NULL);
		if (nb_read == 0)
			break ;
		buffer[nb_read] = '\0';
		save = ft_join(save, buffer, nb_read);
		if (!save)
			return (free(save), free(buffer), NULL);
		i = -1;
		while (save[++i])
			if (save[i] == '\n')
				return (free(buffer), save);
	}
	return (free(buffer), save);
}

static char	*ft_load_line(char *save)
{
	char	*line;
	int		i;

	if (save[0] == '\0')
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = save[i];
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

static char	*ft_clear_save(char *save)
{
	char	*save_cleared;
	int		i;
	int		j;

	if (!save)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	save_cleared = ft_calloc(sizeof(char), (ft_strlen(save) - i + 1));
	if (!save_cleared)
		return (free(save), save_cleared);
	j = 0;
	while (save[i + j])
	{
		save_cleared[j] = save[i + j];
		j++;
	}
	if (save[i + j])
		save_cleared[j] = save[i + j];
	else
		save_cleared[j] = '\0';
	return (free(save), save_cleared);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0)
		return (NULL);
	if (!save)
	{
		save = ft_calloc (1, sizeof(char));
		if (!save)
			return (NULL);
	}
	save = ft_read(fd, save);
	if (!save)
		return (NULL);
	line = ft_load_line(save);
	if (line)
		save = ft_clear_save(save);
	else
	{
		if (save)
			free(save);
		save = NULL;
	}
	return (line);
}
