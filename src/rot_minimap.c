/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:22:14 by phaydont          #+#    #+#             */
/*   Updated: 2019/11/15 14:01:24 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_rot_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall transfo_wall;
	t_vec transfo_player = {surf->w / 2, surf->h / 2};
	t_vec transfo_direc = {surf->w / 2, (surf->h / 2) - 5};
	int i = 0;
	while (i < NB_WALLS) // looping through each existing wall
	{
		double tx1 = (double)walls[i].start_wall.x - player->pos.x;
		double ty1 = (double)walls[i].start_wall.y - player->pos.y;

		double tx2 = (double)walls[i].end_wall.x - player->pos.x;
		double ty2 = (double)walls[i].end_wall.y - player->pos.y;
		
		double tz1 = tx1 * cos(player->angle) + ty1 * sin(player->angle);
		double tz2 = tx2 * cos(player->angle) + ty2 * sin(player->angle);

		tx1 = tx1 * sin(player->angle) - ty1 * cos(player->angle);
		tx2 = tx2 * sin(player->angle) - ty2 * cos(player->angle);

		transfo_wall.start_wall.x = transfo_player.x - tx1;
		transfo_wall.start_wall.y = transfo_player.y - tz1;
		transfo_wall.end_wall.x = transfo_player.x - tx2;
		transfo_wall.end_wall.y = transfo_player.y - tz2;
		
		//draw_line(transfo_wall.start_wall, transfo_wall.end_wall, surf, 0xFFFFFF);
		draw_line(transfo_wall.start_wall, transfo_wall.end_wall, surf, walls[i].color);
		i++;
	}
	draw_line(transfo_player, transfo_direc, surf, 0xFF0000);
	fill_pix(surf, transfo_player.x, transfo_player.y, 0xFFFF00);
}