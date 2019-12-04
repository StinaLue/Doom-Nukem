/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:22:14 by phaydont          #+#    #+#             */
/*   Updated: 2019/12/03 13:37:18 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	init_rotate_wall(t_wall *new_wall, const t_wall *old_wall, const t_player *player)
{
	new_wall->start_wall.x = old_wall->start_wall.x - player->pos.x;
	new_wall->start_wall.y = old_wall->start_wall.y - player->pos.y;
	new_wall->end_wall.x = old_wall->end_wall.x - player->pos.x;
	new_wall->end_wall.y = old_wall->end_wall.y - player->pos.y;
	new_wall->start_wall = rotate2d(new_wall->start_wall, -player->angle);
	new_wall->end_wall = rotate2d(new_wall->end_wall, -player->angle);
}

void	draw_rot_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall transfo_wall;
	t_wall wall_tmp;
	t_vecdb map_center;
	t_vecdb transfo_direc;
	int i;

	i = 0;
	map_center.x = surf->w / 2 +0.5;
	map_center.y = surf->h / 2 +0.5;
	transfo_direc.x = player->inertia.x * 100;
	transfo_direc.y = player->inertia.y * 100;
	transfo_direc = rotate2d(transfo_direc, -player->angle);
	transfo_direc.x = map_center.x + transfo_direc.x;
	transfo_direc.y = map_center.y + transfo_direc.y;

	while (i < NB_WALLS)
	{
		init_rotate_wall(&wall_tmp, &walls[i], player);
		transfo_wall.start_wall.x = map_center.x + wall_tmp.start_wall.x;
		transfo_wall.start_wall.y = map_center.y + wall_tmp.start_wall.y;
		transfo_wall.end_wall.x = map_center.x + wall_tmp.end_wall.x;
		transfo_wall.end_wall.y = map_center.y + wall_tmp.end_wall.y;
		draw_line(vecdb_to_vec(transfo_wall.start_wall), vecdb_to_vec(transfo_wall.end_wall), surf, walls[i].color);
		i++;
	}
	draw_line(vecdb_to_vec(map_center), vecdb_to_vec(transfo_direc), surf, 0xFF8833);
	fill_pix(surf, map_center.x, map_center.y, 0xFFFF00);
}

void	draw_full_rotmap(SDL_Surface *surf, t_player *player, t_wall *walls, SDL_Surface *winsurf)
{
	t_vec topleft_rotmap;
	t_vec topright_rotmap;
	t_vec bottomleft_rotmap;
	t_vec bottomright_rotmap;

	ft_bzero(surf->pixels, surf->h * surf->pitch);
	
	give_vec_values(&topleft_rotmap, 0, 0);
	give_vec_values(&topright_rotmap, MINIMAP_WIDTH - 1, 0);
	give_vec_values(&bottomleft_rotmap, 0, MINIMAP_HEIGHT - 1);
	give_vec_values(&bottomright_rotmap, MINIMAP_WIDTH - 1, MINIMAP_HEIGHT - 1);

	draw_rot_minimap(surf, player, walls);

	draw_line(topleft_rotmap, topright_rotmap, surf, 0xFFFFFF);
	draw_line(bottomleft_rotmap, bottomright_rotmap, surf, 0xFFFFFF);
	draw_line(topleft_rotmap, bottomleft_rotmap, surf, 0xFFFFFF);
	draw_line(topright_rotmap, bottomright_rotmap, surf, 0xFFFFFF);

	blit_in_rect(surf, winsurf, ROT_MAP_SHOW);
}