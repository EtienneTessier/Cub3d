/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:14:06 by etienne           #+#    #+#             */
/*   Updated: 2024/05/27 11:52:50 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t nb, size_t size)
{
	size_t			i;
	unsigned char	*str;

	if (nb == 0 || size == 0)
		return (ft_strdup(""));
	i = 0;
	if (nb && size > (SIZE_MAX / size))
		return (NULL);
	str = malloc(nb * size);
	if (!str)
		return (NULL);
	while (i < nb * size)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}
