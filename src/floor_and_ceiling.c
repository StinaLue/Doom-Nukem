/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:13:39 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/29 20:35:52 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_floor(t_player const *player, t_wall_find *find_wall,
					t_raycast *raycast, t_data *data)
{
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
		//4 different wall directions possible
		if (find_wall->side == 0 && raycast->dir_x > 0)
		{
			floorXWall = raycast->map_x;
			floorYWall = raycast->map_y + find_wall->wall_x;
		}
		else if (find_wall->side == 0 && raycast->dir_x < 0)
		{
			floorXWall = raycast->map_x + 1.0;
			floorYWall = raycast->map_y + find_wall->wall_x;
		}
		else if (find_wall->side == 1 && raycast->dir_y > 0)
		{
			floorXWall = raycast->map_x + find_wall->wall_x;
			floorYWall = raycast->map_y;
		}
		else
		{
			floorXWall = raycast->map_x + find_wall->wall_x;
			floorYWall = raycast->map_y + 1.0;
		}
		double distWall, distPlayer, currentDist;
		distWall = find_wall->distance_wall;
		distPlayer = 0.0;
		if (raycast->end_line < 0)
			raycast->end_line = WIN_HEIGHT;
		for(int y = raycast->end_line + 1; y <= WIN_HEIGHT; y++)
		{
			currentDist = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
			double weight = (currentDist - distPlayer) / (distWall - distPlayer);
			double currentFloorX = weight * floorXWall + (1.0 + weight) * player->x;
			double currentFloorY = weight * floorYWall + (1.0 + weight) * player->y;
			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * TEX_W) % TEX_W;
			floorTexY = (int)(currentFloorY * TEX_H) % TEX_H;
			//printf("floortexx: %d, floortexy: %d\n", floorTexX, floorTexY);
			//int checkerBoardPattern = (int)(currentFloorX + currentFloorY) % 2;
			//if(checkerBoardPattern == 0)
			//	data->tex_num = 3;
			//else
			//	data->tex_num = 0;
			data->color = data->texture[0][TEX_W * floorTexY + floorTexX];
			//data->color = (data->texture[7][TEX_W * floorTexY + floorTexX] >> 1) & 8355711;
			//data->color = data->texture[7][TEX_W * floorTexY + raycast->current_x];
			fill_pix(data->img_ptr, raycast->current_x, y, data->color);
			fill_pix(data->img_ptr, raycast->current_x, WIN_HEIGHT - y, data->color);

		//buffer[y][x] = (texture[floorTexture][TEX_W * floorTexY + floorTexX] >> 1) & 8355711;
		// buffer[WIN_HEIGHT - y][x] = texture[6][TEX_W * floorTexY + floorTexX]; // ceiling
}
}