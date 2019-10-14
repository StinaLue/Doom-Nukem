/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:50:27 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/14 16:56:32 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void	dda_init(t_raycast const *raycast, t_dda *dda)
{
	dda->dir_step_x = (raycast->dir_x < 0 ? -1 : 1);
	dda->dir_step_y = (raycast->dir_y < 0 ? -1 : 1);
	if (raycast->dir_x < 0)
		dda->distance_x_side = dda->dist_x_to_x * (raycast->pos_x - raycast->map_x);
	else
		dda->distance_x_side = dda->dist_x_to_x * (raycast->map_x + 1 - raycast->pos_x);
	if (raycast->dir_y < 0)
		dda->distance_y_side = dda->dist_y_to_y * (raycast->pos_y - raycast->map_y);
	else
		dda->distance_y_side = dda->dist_y_to_y * (raycast->map_y + 1 - raycast->pos_y);
}

void	dda_calculation(t_raycast *raycast, t_dda *dda, t_data const *data)
{
	while (dda->hit == 0 && raycast->map_x < data->map_width && \
			raycast->map_y < data->map_height && raycast->map_x > 0 && raycast->map_y > 0)
	{
		if (dda->distance_x_side < dda->distance_y_side)
		{
			dda->distance_x_side += dda->dist_x_to_x;
			raycast->map_x += dda->dir_step_x;
			dda->side = 0;
		}
		else
		{
			dda->distance_y_side += dda->dist_y_to_y;
			raycast->map_y += dda->dir_step_y;
			dda->side = 1;
		}
		//if (data->map[raycast->map_x][raycast->map_y] > 0)
		if ((*data->map_ptr)[raycast->map_y][raycast->map_x] == 1)
			dda->hit = 1;
	}
}