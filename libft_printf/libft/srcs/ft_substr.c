/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:19:04 by etessier          #+#    #+#             */
/*   Updated: 2024/04/10 11:53:46 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	unsigned int	malloc_len;
	char			*str;

	i = 0;
	s_len = ft_strlen((char *)s);
	if (start > s_len || len == 0 || s[0] == '\0')
		return (ft_strdup(""));
	malloc_len = len;
	if (s_len - start < len)
		malloc_len = s_len - start;
	str = malloc(sizeof(char) * (malloc_len + 1));
	if (!str)
		return (NULL);
	while (s[start + i] != '\0' && (size_t)i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
