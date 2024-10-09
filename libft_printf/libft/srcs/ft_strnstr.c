/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:24:07 by etienne           #+#    #+#             */
/*   Updated: 2024/04/08 14:54:42 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*temp;

	temp = (char *)str;
	i = 0;
	if (to_find[0] == '\0')
		return (temp);
	k = 0;
	while (to_find[k])
		k++;
	while (str[i] != '\0' && i + k <= len)
	{
		j = 0;
		while (str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&temp[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
