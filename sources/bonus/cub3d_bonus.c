/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etessier <etessier@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:44:54 by etessier          #+#    #+#             */
/*   Updated: 2024/10/09 11:47:01 by etessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_param(int argc, char **argv)
{
	int	map_name_len;

	if (argc != 2)
		(ft_putendl_fd(ERR_NB_ARG, 2), exit(1));
	map_name_len = ft_strlen(argv[1]);
	if (map_name_len < 4)
		(ft_putendl_fd(ERR_MAP_EXT, 2), exit(1));
	if (ft_strncmp(&argv[1][map_name_len - 4], ".cub", 4) != 0)
		(ft_putendl_fd(ERR_MAP_EXT, 2), exit(1));
}

static void	game_loop(t_data *data)
{
	mlx_loop_hook(data->mlx, &ray_cast_b, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &handle_key, data);
	mlx_mouse_move(data->mlx, data->win, SCR_WIDTH / 2, SCR_HEIGHT / 2);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, &mouse_move, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, &mouse_click, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &exit_pgm, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_param(argc, argv);
	if (init_data_b(&data, argv[1]) == 1)
	{
		ft_putstr_fd("Error: Init data\n", STDERR_FILENO);
		return (1);
	}
	game_loop(&data);
	free_data(&data);
	return (0);
}
