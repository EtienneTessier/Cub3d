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

#include "../includes/cub3d.h"

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

int	main(int argc, char **argv)
{
	t_data	*data;

	check_param(argc, argv);
	data = init_data(argv[1]);
	if (!data)
		return (1);
	data->win = mlx_new_window(data->mlx, data->width * 64, data->height * 64 \
			, "cub3d");
	ft_printf("ez pz lemon squeezy\n");
	free_data(data);
	return (0);
}
