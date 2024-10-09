/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trt_num_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:24:47 by etienne           #+#    #+#             */
/*   Updated: 2024/05/30 10:47:47 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_size_nb(long nb)
{
	int	size;

	size = 0;
	if (nb < 0)
	{
		nb *= -1;
		size ++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		size++;
	}
	return (++size);
}

static void	ft_print_nb_base10(long nbr)
{
	char		a;
	long int	n;
	const char	*base = BASE_DECI;

	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		n = nbr * (-1);
	}
	else
		n = nbr;
	if (n >= 10)
		ft_print_nb_base10(n / 10);
	a = base[n % 10];
	ft_putchar_fd(a, 1);
}

static void	ft_print_u_nb_base10(unsigned int nbr)
{
	char		a;
	const char	*base = BASE_DECI;

	if (nbr >= 10)
		ft_print_u_nb_base10(nbr / 10);
	a = base[nbr % 10];
	ft_putchar_fd(a, 1);
}

int	ft_trt_nbr(va_list params, char type)
{
	long				nb;
	unsigned int		u_nb;

	nb = 0;
	u_nb = 0;
	if (type == 'u')
		u_nb = va_arg (params, unsigned int);
	else
		nb = va_arg (params, int);
	if (!nb && !u_nb)
		return (ft_putchar_fd('0', 1), 1);
	if (type == 'u')
		return (ft_print_u_nb_base10(u_nb), ft_size_nb(u_nb));
	else if (type == 'i' || type == 'd')
		return (ft_print_nb_base10(nb), ft_size_nb(nb));
	else
		return (0);
}
