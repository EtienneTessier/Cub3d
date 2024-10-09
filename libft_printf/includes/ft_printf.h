/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:33:52 by etessier          #+#    #+#             */
/*   Updated: 2024/05/30 11:00:28 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include "../libft/include/libft.h"

# define BASE_HEXA_LOW "0123456789abcdef"
# define BASE_HEXA_UPP "0123456789ABCDEF"
# define BASE_DECI "0123456789"

int	ft_printf(const char *str, ...);

int	ft_trt_nbr(va_list params, char type);

int	ft_trt_nbr_hexa(va_list params, char *base, char top_case);

#endif
