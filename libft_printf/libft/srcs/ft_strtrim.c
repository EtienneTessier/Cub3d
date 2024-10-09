/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:28:50 by etienne           #+#    #+#             */
/*   Updated: 2024/04/10 15:55:04 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t		start;
	size_t		end;
	size_t		size;

	start = 0;
	end = 0;
	size = ft_strlen(s1);
	while (s1[start] && ft_is_set(s1[start], set))
		start++;
	while (s1[size - end - 1] && ft_is_set(s1[size - end - 1], set))
		end++;
	return (ft_substr(s1, start, size - (start + end)));
}
