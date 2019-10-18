/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall_calculation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:50:27 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/18 02:18:28 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	find_wall_init(t_raycast const *raycast, t_wall_finding *find_wall)
{
	find_wall->dir_step_x = (raycast->dir_x < 0 ? -1 : 1);
	find_wall->dir_step_y = (raycast->dir_y < 0 ? -1 : 1);
	if (raycast->dir_y < 0)
		find_wall->distance_y_side =
				find_wall->dist_y_to_y * (raycast->pos_y - raycast->map_y);
	else
		find_wall->distance_y_side =
				find_wall->dist_y_to_y * (raycast->map_y + 1 - raycast->pos_y);
	if (raycast->dir_x < 0)
		find_wall->distance_x_side =
				find_wall->dist_x_to_x * (raycast->pos_x - raycast->map_x);
	else
		find_wall->distance_x_side =
				find_wall->dist_x_to_x * (raycast->map_x + 1 - raycast->pos_x);
}

void	find_wall_calculation(t_raycast *raycast, t_wall_finding *find_wall,
								t_data const *data)
{
	while (find_wall->hit == 0 && raycast->map_x < data->map_width && \
			raycast->map_y < data->map_height && raycast->map_x > 0 && \
			raycast->map_y > 0)
	{
		if (find_wall->distance_x_side < find_wall->distance_y_side)
		{
			find_wall->distance_x_side += find_wall->dist_x_to_x;
			raycast->map_x += find_wall->dir_step_x;
			find_wall->side = 0;
		}
		else
		{
			find_wall->distance_y_side += find_wall->dist_y_to_y;
			raycast->map_y += find_wall->dir_step_y;
			find_wall->side = 1;
		}
		if (is_valid_wall((*data->map_ptr)[raycast->map_y][raycast->map_x]) == 1)
			find_wall->hit = 1;
	}
}
