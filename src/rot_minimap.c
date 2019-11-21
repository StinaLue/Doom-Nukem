/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:22:14 by phaydont          #+#    #+#             */
/*   Updated: 2019/11/21 15:39:27 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_rotate_wall(t_wall *new_wall, const t_wall *old_wall, const t_player *player)
{
	new_wall->start_wall.x = old_wall->start_wall.x - player->pos.x;
	new_wall->start_wall.y = old_wall->start_wall.y - player->pos.y;
	new_wall->end_wall.x = old_wall->end_wall.x - player->pos.x;
	new_wall->end_wall.y = old_wall->end_wall.y - player->pos.y;
	new_wall->start_wall = rotate2d(new_wall->start_wall, player->angle);
	new_wall->end_wall = rotate2d(new_wall->end_wall, player->angle);
}

void	draw_rot_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall transfo_wall;
	t_wall wall_tmp;
	t_vecdb transfo_player;
	t_vecdb transfo_direc;
	int i;

	i = 0;
	transfo_player.x = surf->w / 2;
	transfo_player.y = surf->h / 2;
	transfo_direc.x = surf->w / 2;
	transfo_direc.y = (surf->h / 2) - 5;
	while (i < NB_WALLS)
	{
		init_rotate_wall(&wall_tmp, &walls[i], player);
		transfo_wall.start_wall.x = transfo_player.x - wall_tmp.start_wall.y + 1;
		transfo_wall.start_wall.y = transfo_player.y - wall_tmp.start_wall.x + 1;
		transfo_wall.end_wall.x = transfo_player.x - wall_tmp.end_wall.y + 1;
		transfo_wall.end_wall.y = transfo_player.y - wall_tmp.end_wall.x + 1;
		draw_line(vecdb_to_vec(transfo_wall.start_wall), vecdb_to_vec(transfo_wall.end_wall), surf, walls[i].color);
		i++;
	}
	draw_line(vecdb_to_vec(transfo_player), vecdb_to_vec(transfo_direc), surf, 0xFF0000);
	fill_pix(surf, transfo_player.x, transfo_player.y, 0xFFFF00);
}

void	draw_full_rotmap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_vec topleft_rotmap;// = {0, 0};
	t_vec topright_rotmap;// = {ROT_MAP_WIDTH - 1, 0};
	t_vec bottomleft_rotmap;// = {0, ROT_MAP_HEIGHT - 1};
	t_vec bottomright_rotmap;// = {ROT_MAP_WIDTH - 1, ROT_MAP_HEIGHT - 1};

	give_vec_values(&topleft_rotmap, 0, 0);
	give_vec_values(&topright_rotmap, ROT_MAP_WIDTH - 1, 0);
	give_vec_values(&bottomleft_rotmap, 0, ROT_MAP_HEIGHT - 1);
	give_vec_values(&bottomright_rotmap, ROT_MAP_WIDTH - 1, ROT_MAP_HEIGHT - 1);
	draw_line(topleft_rotmap, topright_rotmap, surf, 0xFFFFFF);
	draw_line(bottomleft_rotmap, bottomright_rotmap, surf, 0xFFFFFF);
	draw_line(topleft_rotmap, bottomleft_rotmap, surf, 0xFFFFFF);
	draw_line(topright_rotmap, bottomright_rotmap, surf, 0xFFFFFF);
	draw_rot_minimap(surf, player, walls);
}