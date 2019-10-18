/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:35:15 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/18 03:24:07 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include <math.h>

void	ray_init(t_raycast *raycast, t_player const *player)
{
	raycast->camera = 2 * raycast->current_x / (double)WIN_WIDTH - 1;
	raycast->pos_x = player->x;
	raycast->pos_y = player->y;
	raycast->dir_x = player->x_dir + player->fov_x * raycast->camera;
	raycast->dir_y = player->y_dir + player->fov_y * raycast->camera;
	raycast->map_x = (int)raycast->pos_x;
	raycast->map_y = (int)raycast->pos_y;
	raycast->height = 0;
	raycast->start_line = 0;
	raycast->end_line = 0;
}

void	height_calculation(t_raycast *raycast, t_wall_finding *find_wall,
							int updown, double crouch)
{
	if (find_wall->side == X_SIDE)
		find_wall->distance_wall = ft_absfloat((raycast->map_x - raycast->pos_x
					+ (1 - find_wall->dir_step_x) / 2) / raycast->dir_x);
	else
		find_wall->distance_wall = ft_absfloat((raycast->map_y - raycast->pos_y
					+ (1 - find_wall->dir_step_y) / 2) / raycast->dir_y);
	raycast->height = ft_absolute((int)(WIN_HEIGHT / find_wall->distance_wall));
	raycast->start_line = -raycast->height / 2 + WIN_HEIGHT / 2
						+ updown - crouch;
	raycast->end_line = raycast->height / 2 + WIN_HEIGHT / 2 + updown - crouch;
	if (raycast->start_line < 0)
		raycast->start_line = 0;
	if (raycast->end_line >= WIN_HEIGHT)
		raycast->end_line = WIN_HEIGHT - 1;
}

void	raycasting(t_player const *player, t_raycast *raycast,
					t_wall_finding *find_wall, t_data *data)
{
	ray_init(raycast, player);
	find_wall_init(raycast, find_wall);
	find_wall_calculation(raycast, find_wall, data);
	height_calculation(raycast, find_wall, player->up_and_down, player->crouch);
	draw_tex(player, find_wall, raycast, data);
	draw_vertical(data->img_ptr, raycast->current_x,
					raycast->end_line, WIN_HEIGHT, 0x808080);
	draw_vertical(data->img_ptr, raycast->current_x, 0,
					raycast->start_line, 0x87CEFA);
}

void	*iterate_raycast(void *param)
{
	t_wolf	*wolf;

	wolf = (t_wolf *)param;
	wolf->raycast.current_x = wolf->data.start_thread;
	while (wolf->raycast.current_x < wolf->data.end_thread)
	{
		raycasting(&(wolf->player), &(wolf->raycast),
					&(wolf->find_wall), &(wolf->data));
		wolf->raycast.current_x++;
	}
	return (NULL);
}

/*
**	Do the raycasting for all the threads
*/
