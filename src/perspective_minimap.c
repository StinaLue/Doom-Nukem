/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_minimap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/14 18:32:32 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_perspective_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall3d transfo_wall; // need t_wall3d because we have to access more values than just x and y (top/bottom/left/right)
	(void)player;
	int i = 0;
	while (i < NB_WALLS) // looping through each existing wall
	{
		double tx1 = walls[i].start_wall.x - player->pos.x;
		double ty1 = walls[i].start_wall.y - player->pos.y;

		double tx2 = walls[i].end_wall.x - player->pos.x;
		double ty2 = walls[i].end_wall.y - player->pos.y;

		double tz1 = tx1 * cos(player->angle) + ty1 * sin(player->angle);
		double tz2 = tx2 * cos(player->angle) + ty2 * sin(player->angle);

		tx1 = tx1 * sin(player->angle) - ty1 * cos(player->angle);
		tx2 = tx2 * sin(player->angle) - ty2 * cos(player->angle);
		if (tz1 == 0)
			tz1 = 0.00001;
		if (tz2 == 0)
			tz2 = 0.00001;
		double x1 = -tx1 * 16 / tz1; // perspective works because of division of x and y coordinates by z -> matrix
		double x2 = -tx2 * 16 / tz2;
		double y1a = -50 / tz1;
		double y2a = -50 / tz2;
		double y1b = 50 / tz1;
		double y2b = 50 / tz2;
		transfo_wall.top_left.x = 50 + x1;
		transfo_wall.top_left.y = 50 + y1a;
		transfo_wall.top_right.x = 50 + x2;
		transfo_wall.top_right.y = 50 + y2a;
		transfo_wall.bottom_left.x = 50 + x1;
		transfo_wall.bottom_left.y = 50 + y1b;
		transfo_wall.bottom_right.x = 50 + x2;
		transfo_wall.bottom_right.y = 50 + y2b;
		draw_line(transfo_wall.top_left, transfo_wall.top_right, surf, 0xFFFFFF); // drawing a line for each line around wall
		draw_line(transfo_wall.top_right, transfo_wall.bottom_right, surf, 0xFFFFFF);
		draw_line(transfo_wall.bottom_right, transfo_wall.bottom_left, surf, 0xFFFFFF);
		draw_line(transfo_wall.bottom_left, transfo_wall.top_left, surf, 0xFFFFFF);
		i++;
	}
}