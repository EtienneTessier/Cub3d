/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:19:27 by etienne           #+#    #+#             */
/*   Updated: 2024/04/17 10:36:33 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_count_parts(long n, int *sign)
{
	int	i;

	*sign = 1;
	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		*sign *= -1;
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		sign;
	int		nb_parts;
	long	nb;

	nb = n;
	nb_parts = ft_count_parts(nb, &sign);
	number = malloc(sizeof(char) * (nb_parts + 1));
	if (!number)
		return (NULL);
	nb = nb * sign;
	number[nb_parts] = '\0';
	nb_parts--;
	if (n == 0)
		number[0] = '0';
	if (sign < 0)
		number[0] = '-';
	while (nb > 0)
	{
		number[nb_parts] = (nb % 10) + '0';
		nb = nb / 10;
		nb_parts--;
	}
	return (number);
}
