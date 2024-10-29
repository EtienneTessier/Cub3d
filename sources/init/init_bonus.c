/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienne <etienne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:18:23 by etienne           #+#    #+#             */
/*   Updated: 2024/10/25 10:18:24 by etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_bonus(t_data *data)
{
	if (init_textures_bonus(data))
		return (1);
	if (init_ennemis(data))
		return (1);
	if (crea_minimap(data))
		return (1);
	return (0);
}
