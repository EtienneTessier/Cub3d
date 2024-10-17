/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:41:15 by etessier          #+#    #+#             */
/*   Updated: 2024/10/15 11:41:16 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	// ft_printf("x = %d\n", x);
	// ft_printf("y = %d\n", y);
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	// ft_printf("dst = %p\n", dst);
	*(unsigned int *)dst = color;
}

void	load_col(int x, t_ray ray, int color, t_data *data)
{
	int	y;

	y = 0;
	while (y < ray.draw_start)
	{
		my_mlx_pixel_put(data->img, x, y, BLA_PIXEL);
		y++;
	}
	while (y >= ray.draw_start && y <= ray.draw_end)
	{
		my_mlx_pixel_put(data->img, x, y, color);
		y++;
	}
	while (y < SCR_HEIGHT - 1)
	{
		my_mlx_pixel_put(data->img, x, y, DBL_PIXEL);
		y++;
	}
}
