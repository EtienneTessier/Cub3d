/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:49:14 by etienne           #+#    #+#             */
/*   Updated: 2024/05/21 17:37:33 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*temp_dest;
	unsigned char	*temp_src;

	if (!dest && !src)
		return (NULL);
	i = 0;
	temp_dest = (unsigned char *)dest;
	temp_src = (unsigned char *)src;
	if (dest > src)
	{
		while (n > i)
		{
			temp_dest[n - 1] = temp_src[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
