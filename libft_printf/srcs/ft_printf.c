/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:33:22 by etessier          #+#    #+#             */
/*   Updated: 2024/05/28 11:29:06 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>

static int	ft_trt_chars(va_list params, char type)
{
	char	c;
	char	*str;

	if (type == 'c')
	{
		c = va_arg (params, int);
		ft_putchar_fd(c, 1);
		return (1);
	}
	else if (type == 's')
	{
		str = va_arg (params, char *);
		if (!str)
			return (ft_printf("(null)"));
		ft_putstr_fd(str, 1);
		return (ft_strlen(str));
	}
	return (0);
}

static int	ft_trt_params(char c, va_list params)
{
	if (c == 'c' || c == 's')
		return (ft_trt_chars(params, c));
	else if (c == 'd' || c == 'i' || c == 'u')
		return (ft_trt_nbr(params, c));
	else if (c == 'p' || c == 'x')
		return (ft_trt_nbr_hexa(params, BASE_HEXA_LOW, c));
	else if (c == 'X')
		return (ft_trt_nbr_hexa(params, BASE_HEXA_UPP, c));
	else if (c == '%')
		return (ft_putchar_fd('%', 1), 1);
	else
		return (ft_putchar_fd('%', 1), ft_putchar_fd(c, 1), 2);
}

static int	ft_print(const char *str, va_list params)
{
	int	i;
	int	total_print;

	i = 0;
	total_print = 0;
	while (str[i])
	{
		if (str[i] != '%' && str[i] != '\0')
		{
			ft_putchar_fd(str[i], 1);
			total_print++;
		}
		else if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				return (-1);
			total_print += ft_trt_params(str[++i], params);
		}
		else
			return (-1);
		i++;
	}
	return (total_print);
}

int	ft_printf(const char *str, ...)
{
	va_list	params;
	int		total_print;

	if (!str)
		return (-1);
	va_start(params, str);
	total_print = ft_print(str, params);
	va_end(params);
	return (total_print);
}
