/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:35:15 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/15 17:13:10 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include <math.h>

void	fill_tex(int texture[4][TEX_W * TEX_H])
{
	int x = 0;
	int y;

	while (x < TEX_W)
	{
		y = 0;
	  while (y < TEX_H)
	  {
		    int xorcolor = (x * 256 / TEX_W) ^ (y * 256 / TEX_H);
		    //int xcolor = x * 256 / TEX_W;
		    //int ycolor = y * 256 / TEX_H;
		    int xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
		    texture[0][TEX_W * y + x] = 65536 * 254 * (x != y && x != TEX_W - y); //flat red texture with black cross
		    texture[1][TEX_W * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
		    texture[2][TEX_W * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
		    texture[3][TEX_W * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
		    //texture[4][TEX_W * y + x] = 256 * xorcolor; //xor green
		    //texture[5][TEX_W * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
		    //texture[6][TEX_W * y + x] = 65536 * ycolor; //red gradient
		    //texture[7][TEX_W * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
			y++;
 	 	}
		  x++;
	}
}

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
		double	wallx;
		int		tex_x;
		int		tex_num = 0;

        color = 0;
        ray_init(raycast, find_wall, player, x);
        find_wall_init(raycast, find_wall);
        find_wall_calculation(raycast, find_wall, data);
        if ((*data->map_ptr)[raycast->map_y][raycast->map_x] == 1)
			tex_num = 0;
        if (find_wall->side == 0 && player->x < raycast->map_x)
			tex_num = 1;
        if (find_wall->side == 1)
        {
            if (player->y < raycast->map_y)
				tex_num = 2;
			else
				tex_num = 3;
		}
			
        height_calculation(raycast, find_wall, player->up_and_down, player->crouch);
		if (find_wall->side == 0)
			wallx = player->y + find_wall->distance_wall * raycast->dir_y;
		else
			wallx = player->x + find_wall->distance_wall * raycast->dir_x;
		wallx -= floor(wallx);
		tex_x = (int)(wallx * (double)TEX_W);
		if (find_wall->side == 0 && raycast->dir_x > 0)
			tex_x = TEX_W - tex_x - 1;
		if (find_wall->side == 1 && raycast->dir_y < 0)
			tex_x = TEX_W - tex_x - 1;
		for(int y = raycast->start_line; y < raycast->end_line; y++)
      {
        int d = y * 256 - WIN_HEIGHT * 128 + raycast->height * 128 - (player->up_and_down - player->crouch) * 256;  //256 and 128 factors to avoid floats
        // TODO: avoid the division to speed this up
        int texY = ((d * TEX_H) / raycast->height) / 256;
        Uint32 color = data->texture[tex_num][TEX_H * texY + tex_x];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(find_wall->side == 1) color = (color >> 1) & 8355711;
        fill_pix(data->img_ptr, x, y, color);
      }
		
        //draw_vertical(data->img_ptr, x, raycast->start_line, raycast->end_line, color);
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
