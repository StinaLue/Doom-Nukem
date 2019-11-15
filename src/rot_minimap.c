/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:22:14 by phaydont          #+#    #+#             */
/*   Updated: 2019/11/15 15:57:40 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vecdb	rotate2d(t_vecdb vector, double angle)
{
	t_vecdb newvector;

	newvector.x = vector.x * cos(angle) + vector.y * sin(angle);
	newvector.y = vector.x * sin(angle) - vector.y * cos(angle);
	return (newvector);
}

t_vec	vecdb_to_vec(t_vecdb vectordb)
{
	t_vec vector;

	vector.x = (int)vectordb.x;
	vector.y = (int)vectordb.y;
	return (vector);
}

void	draw_rot_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall transfo_wall;
	t_vecdb transfo_player = {surf->w / 2, surf->h / 2};
	t_vecdb transfo_direc = {surf->w / 2, (surf->h / 2) - 5};
	int i = 0;
	while (i < NB_WALLS)
	{
		t_vecdb startwall;
		t_vecdb endwall;
		t_vecdb rotstartwall;
		t_vecdb rotendwall;

		startwall.x = (double)walls[i].start_wall.x - player->pos.x;
		startwall.y = (double)walls[i].start_wall.y - player->pos.y;

		endwall.x = (double)walls[i].end_wall.x - player->pos.x;
		endwall.y = (double)walls[i].end_wall.y - player->pos.y;
		
		rotstartwall = rotate2d(startwall, player->angle);
		rotendwall = rotate2d(endwall, player->angle);

		transfo_wall.start_wall.x = transfo_player.x - rotstartwall.y;
		transfo_wall.start_wall.y = transfo_player.y - rotstartwall.x;
		transfo_wall.end_wall.x = transfo_player.x - rotendwall.y;
		transfo_wall.end_wall.y = transfo_player.y - rotendwall.x;
		draw_line(transfo_wall.start_wall, transfo_wall.end_wall, surf, walls[i].color);
		i++;
	}
	draw_line(vecdb_to_vec(transfo_player), vecdb_to_vec(transfo_direc), surf, 0xFF0000);
	fill_pix(surf, transfo_player.x, transfo_player.y, 0xFFFF00);
}