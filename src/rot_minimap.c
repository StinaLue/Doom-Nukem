/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:22:14 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/07 16:14:52 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	init_rotate_wall(t_wall *new_wall, const t_wall_node *current_wall, const t_player *player)
{
	new_wall->start_wall.x = current_wall->start_wall.x - player->pos.x;
	new_wall->start_wall.y = current_wall->start_wall.y - player->pos.y;
	new_wall->end_wall.x = current_wall->end_wall.x - player->pos.x;
	new_wall->end_wall.y = current_wall->end_wall.y - player->pos.y;
	new_wall->start_wall = rotate2d(new_wall->start_wall, -player->angle);
	new_wall->end_wall = rotate2d(new_wall->end_wall, -player->angle);
}

void	draw_rot_minimap(SDL_Surface *surf, t_player *player, const t_map *map)
{
	t_wall transfo_wall;
	t_wall wall_tmp;
	t_vecdb map_center;
	t_vecdb transfo_direc;
	t_wall_node *current_wall;
	
	map_center.x = surf->w / 2 +0.5;
	map_center.y = surf->h / 2 +0.5;
	transfo_direc.x = player->inertia.x * 100;
	transfo_direc.y = player->inertia.y * 100;
	transfo_direc = rotate2d(transfo_direc, -player->angle);
	transfo_direc.x = map_center.x + transfo_direc.x;
	transfo_direc.y = map_center.y + transfo_direc.y;

	current_wall = map->sector_head->wall_head;

	while (current_wall != NULL)
	{
		init_rotate_wall(&wall_tmp, current_wall, player);
		transfo_wall.start_wall.x = map_center.x + wall_tmp.start_wall.x;
		transfo_wall.start_wall.y = map_center.y + wall_tmp.start_wall.y;
		transfo_wall.end_wall.x = map_center.x + wall_tmp.end_wall.x;
		transfo_wall.end_wall.y = map_center.y + wall_tmp.end_wall.y;
		draw_line(vecdb_to_vec(transfo_wall.start_wall), vecdb_to_vec(transfo_wall.end_wall), surf, current_wall->color);
		current_wall = current_wall->next;
	}
	draw_line(vecdb_to_vec(map_center), vecdb_to_vec(transfo_direc), surf, 0xFF8833);
	fill_pix(surf, map_center.x, map_center.y, 0xFFFF00);
}

int		draw_full_rotmap(SDL_Surface *surf, t_player *player, const t_map *map, SDL_Surface *winsurf)
{
	int ret;

	ret = 0;
	ft_bzero(surf->pixels, surf->h * surf->pitch);
	draw_rot_minimap(surf, player, map);
	draw_border(surf, 0xFFFFFF);

	ret = blit_in_rect(surf, winsurf, ROT_MAP_SHOW);
	return (ret);
}
