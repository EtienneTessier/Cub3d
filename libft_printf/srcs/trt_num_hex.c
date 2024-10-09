/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trt_num_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:46:43 by etessier          #+#    #+#             */
/*   Updated: 2024/05/30 10:54:26 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_ptr(unsigned long long nbr, char *base)
{
	char	a;

	if (nbr >= 16)
		ft_print_ptr(nbr / 16, base);
	a = base[nbr % 16];
	ft_putchar_fd(a, 1);
}

static void	ft_print_hexa(unsigned int nbr, char *base)
{
	char	a;

	if (nbr >= 16)
		ft_print_hexa(nbr / 16, base);
	a = base[nbr % 16];
	ft_putchar_fd(a, 1);
}

static int	ft_hexa_len(unsigned long long nbr)
{
	int	size;

	size = 0;
	while (nbr >= 16)
	{
		nbr /= 16;
		size++;
	}
	return (size + 1);
}

int	ft_trt_nbr_hexa(va_list params, char *base, char top_case)
{
	unsigned long long	ull_nbr;
	unsigned int		nbr;
	int					size;

	size = 0;
	if (top_case == 'p')
	{
		ull_nbr = va_arg(params, unsigned long long);
		if (ull_nbr == 0)
			return (ft_putstr_fd("(nil)", 1), 5);
		ft_putstr_fd("0x", 1);
		size += 2;
		ft_print_ptr(ull_nbr, base);
		return (size + ft_hexa_len(ull_nbr));
	}
	else
	{
		nbr = va_arg(params, unsigned int);
		ft_print_hexa(nbr, base);
		return (size + ft_hexa_len(nbr));
	}
}
