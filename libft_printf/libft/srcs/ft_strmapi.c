/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:54:11 by etienne           #+#    #+#             */
/*   Updated: 2024/04/17 17:05:19 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		i;
	size_t		s_len;
	char		*mapied;

	s_len = ft_strlen(s);
	mapied = malloc (sizeof(char) * (s_len + 1));
	if (!mapied)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		mapied[i] = (*f)(i, s[i]);
		i++;
	}
	mapied[i] = '\0';
	return (mapied);
}
