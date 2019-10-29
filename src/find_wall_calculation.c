/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall_calculation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:50:27 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/29 15:27:04 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	find_wall_init(t_raycast const *raycast, t_wall_find *find_wall)
{
	find_wall->dist_x_to_x = ft_absfloat(1 / (raycast->dir_x != 0 ?
							raycast->dir_x : 0.00001));
	find_wall->dist_y_to_y = ft_absfloat(1 / (raycast->dir_y != 0 ?
							raycast->dir_y : 0.00001));
	find_wall->hit = 0;
	find_wall->side = 0;
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

void	find_wall_calculation(t_raycast *raycast, t_wall_find *find_wall,
								t_data const *data)
{
	while (find_wall->hit == 0 && raycast->map_x < data->map_width && \
			raycast->map_y < data->map_height && raycast->map_x > 0 && \
			raycast->map_y > 0)
	{
		find_wall->side = (find_wall->distance_x_side > \
			find_wall->distance_y_side ? Y_SIDE : X_SIDE);
		if (find_wall->distance_x_side > find_wall->distance_y_side)
		{
			find_wall->distance_y_side += find_wall->dist_y_to_y;
			raycast->map_y += find_wall->dir_step_y;
		}
		else
		{
			find_wall->distance_x_side += find_wall->dist_x_to_x;
			raycast->map_x += find_wall->dir_step_x;
		}
		if (is_valid_wall((*data->map_ptr)[raycast->map_x][raycast->map_y]) \
			== 1)
			find_wall->hit = 1;
	}
}
