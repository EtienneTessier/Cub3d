/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:13:53 by etienne           #+#    #+#             */
/*   Updated: 2024/04/08 10:57:55 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	counter_src;
	size_t	len_dest;
	size_t	len_src;

	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size <= len_dest)
		return (len_src + size);
	else
	{
		counter_src = 0;
		while (src[counter_src] != '\0' && (len_dest + counter_src) < size - 1)
		{
			dst[len_dest + counter_src] = src[counter_src];
			counter_src++;
		}
	}
	dst[len_dest + counter_src] = '\0';
	return (len_dest + len_src);
}
