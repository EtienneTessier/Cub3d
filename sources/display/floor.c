/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:56:27 by etienne           #+#    #+#             */
/*   Updated: 2024/11/05 15:56:28 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_floor(t_data *data)
{
	// t_ray	ray;
	int	y;
	int	x;

	y = SCR_HEIGHT / 2;
	while (y < SCR_HEIGHT)
    {
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
      float rayDirX0 = data->player.dir_x - data->player.plan_x;
      float rayDirY0 = data->player.dir_y - data->player.plan_y;
      float rayDirX1 = data->player.dir_x + data->player.plan_x;
      float rayDirY1 = data->player.dir_y + data->player.plan_y;

      // Current y position compared to the center of the screen (the horizon)
      int pos = y - SCR_HEIGHT / 2;

      // Vertical position of the camera.
      float posZ = 0.5 * SCR_HEIGHT;

      /*// Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.*/
      float rowDistance = posZ / pos;

      /*// calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop*/
      float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCR_WIDTH;
      float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCR_WIDTH;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      float floorX = data->player.x + rowDistance * rayDirX0;
      float floorY = data->player.y + rowDistance * rayDirY0;

		x = 0;
      while (x < SCR_WIDTH)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);

        // get the texture coordinate from the fractional part
        int tx = (int)(data->txr->width * (floorX - cellX)) & (data->txr->width - 1);
        int ty = (int)(data->txr->height * (floorY - cellY)) & (data->txr->height - 1);

        floorX += floorStepX;
        floorY += floorStepY;

        /*// choose texture and draw the pixel
        int32_t color;

        // floor
        color = data->txr->floor_txr[data->txr->width * ty + tx];*/
		my_mlx_pixel_put(data->img, x, y, data->txr->floor_txr[data->txr->width * ty + tx]);
        /*// color = (color >> 1) & 8355711; // make a bit darker
        // buffer[y][x] = color;

        // //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
        // color = texture[ceilingTexture][texWidth * ty + tx];
        // color = (color >> 1) & 8355711; // make a bit darker
        // buffer[screenHeight - y - 1][x] = color;*/
		x++;
      }
	  y++;
    }
}
