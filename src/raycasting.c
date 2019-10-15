/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:35:15 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/15 13:49:44 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void	ray_init(t_raycast *raycast, t_wall_finding *find_wall, t_player const *player, int x)
{
	raycast->cam_x = 2 * x / (double)WIN_WIDTH - 1;

	raycast->pos_x = player->x;
	raycast->pos_y = player->y;

	raycast->dir_x = player->x_dir + player->cam_vector_x * raycast->cam_x;
	raycast->dir_y = player->y_dir + player->cam_vector_y * raycast->cam_x;
	raycast->map_x = (int)raycast->pos_x;
	raycast->map_y = (int)raycast->pos_y;

	raycast->height = 0;
	raycast->start_line = 0;
	raycast->end_line = 0;

	/*
	** SEEMS LIKE BOTH OF THE FOLLOWING METHODS WORK
	*/
	if (raycast->dir_x != 0)
		find_wall->dist_x_to_x = ft_absfloat(1 / raycast->dir_x);
	else
		find_wall->dist_x_to_x = ft_absfloat(1 / 0.00001); // MAYBE A BUG, WORKS FOR NOW THO?
	if (raycast->dir_y != 0)
		find_wall->dist_y_to_y = ft_absfloat(1 / raycast->dir_y);
	else
		find_wall->dist_y_to_y = ft_absfloat(1 / 0.00001);
	//find_wall->dist_x_to_x = sqrt(1 + (raycast->dir_y * raycast->dir_y) / (raycast->dir_x * raycast->dir_x));
	//find_wall->dist_y_to_y = sqrt(1 + (raycast->dir_x * raycast->dir_x) / (raycast->dir_y * raycast->dir_y));
	find_wall->hit = 0;
	find_wall->side = 0;
}

void	height_calculation(t_raycast *raycast, t_wall_finding *find_wall, int updown, double crouch)
{
	if (find_wall->side == 0)
		find_wall->distance_wall = /*(raycast->dir_x == 0.0) ? 0 : */ft_absfloat((raycast->map_x -
					raycast->pos_x + (1 - find_wall->dir_step_x) / 2) / raycast->dir_x);
	else
		find_wall->distance_wall = /*(raycast->dir_y == 0.0) ? 0 :*/ft_absfloat((raycast->map_y -
					raycast->pos_y + (1 - find_wall->dir_step_y) / 2) / raycast->dir_y);
	//if (find_wall->distance_wall != 0)
		raycast->height = ft_absolute((int)(WIN_HEIGHT / find_wall->distance_wall));
//	else
//		raycast->height = 0;
	raycast->start_line = -raycast->height / 2 + WIN_HEIGHT / 2 + updown - crouch * 1.2;
	raycast->end_line = raycast->height / 2 + WIN_HEIGHT / 2 + updown - crouch;
	if (raycast->start_line < 0)
		raycast->start_line = 0;
	if (raycast->end_line >= WIN_HEIGHT)
		raycast->end_line = WIN_HEIGHT - 1;
}

void    raycasting(t_player const *player, t_raycast *raycast, t_wall_finding *find_wall, t_data *data, int x)
{
        int     color;

        color = 0;
        ray_init(raycast, find_wall, player, x);
        find_wall_init(raycast, find_wall);
        find_wall_calculation(raycast, find_wall, data);
        height_calculation(raycast, find_wall, player->up_and_down, player->crouch);
        /*switch(data->map[raycast->map_x][raycast->map_y])
          {
          case 1:  color = 16711680;  break; //red
          case 2:  color = 65280;  break; //green
          case 3:  color = 255;   break; //blue
          case 4:  color = 16777215;  break; //white
          default: color = 16776960; break; //yellow
          }*/
        if ((*data->map_ptr)[raycast->map_y][raycast->map_x] == 1)
                color = 230;
        if (find_wall->side == 0 && player->x < raycast->map_x)
                color = 16711680;
        if (find_wall->side == 1)
        {
                if (player->y < raycast->map_y)
                        color = color / 2;
                else
                        color = color / 5;
        }
        draw_vertical(data->img_ptr, x, raycast->start_line, raycast->end_line, color);
        draw_vertical(data->img_ptr, x, raycast->end_line, WIN_HEIGHT, 0x808080);
        draw_vertical(data->img_ptr, x, 0, raycast->start_line, 0xC8C8C8);
        /*
        **      if (x == 450 || x == 451)
        **      {
        **      ft_printf("cam_x %f color is: %d start_line: %d, end_line: %d and x: %d\n", raycast->cam_x, color, raycast->start_line, raycast->end_line, x);
        **      ft_printf("AND height = %d\n", raycast->height);
        **      }
        */
}

void	*iterate_raycast(void *param)
{
	t_wolf	*wolf;
	int		x;

	wolf = (t_wolf *)param;
	x = wolf->data.start_thread;
	while (x < wolf->data.end_thread)
	{
		raycasting(&(wolf->player), &(wolf->raycast), &(wolf->find_wall), &(wolf->data), x);
		x++;
	}
	return (NULL);
}
