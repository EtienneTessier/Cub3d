/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:11:15 by etessier          #+#    #+#             */
/*   Updated: 2024/10/09 14:11:16 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	skip_char(char *str, char to_skip)
{
	int	i;

	i = 0;
	while (str[i] == to_skip)
		i++;
	return (i);
}

char	*crea_row(char c, int size)
{
	int		i;
	char	*row;

	row = ft_calloc(size + 1, sizeof(char));
	if (!row)
		return (NULL);
	i = 0;
	while (i < size)
	{
		row[i] = c;
		i++;
	}
	row[i] = '\0';
	return (row);
}
