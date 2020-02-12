/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:22:14 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/12 11:32:36 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

t_segment	rotate_wall_relative(const t_wall_node *current_wall, \
									const t_player *player)
{
	t_segment	new_wall;

	new_wall.a = vecdb_diff(current_wall->start, player->pos);
	new_wall.b = vecdb_diff(current_wall->end, player->pos);
	new_wall.a = rotate2d(new_wall.a, -player->angle);
	new_wall.b = rotate2d(new_wall.b, -player->angle);
	return (new_wall);
}

void		draw_wall(t_wall_node *node, t_player *player, SDL_Surface *surf)
{
	t_segment		wall;
	t_vecdb			map_center;

	while (node != NULL)
	{
		map_center.x = surf->w / 2 + 0.5;
		map_center.y = surf->h / 2 + 0.5;
		wall = rotate_wall_relative(node, player);
		wall.a = vecdb_add(map_center, multvecdb(wall.a, 0.25));
		wall.b = vecdb_add(map_center, multvecdb(wall.b, 0.25));
		draw_line(vecdb_to_vec(wall.a), vecdb_to_vec(wall.b), surf, \
			node->neighbor_sector == NULL ? 0xEEEEEE : 0x333333);
		node = node->next;
	}
}

void		draw_rot_minimap(SDL_Surface *surf, \
								t_player *player, const t_map *map)
{
	t_vecdb			map_center;
	t_vecdb			transfo_direc;
	t_sector_node	*current_sector;

	map_center.x = surf->w / 2 + 0.5;
	map_center.y = surf->h / 2 + 0.5;
	transfo_direc = multvecdb(player->inertia, 100);
	transfo_direc = rotate2d(transfo_direc, -player->angle);
	transfo_direc = vecdb_add(map_center, transfo_direc);
	current_sector = map->sector_head;
	while (current_sector != NULL)
	{
		draw_wall(current_sector->wall_head, player, surf);
		current_sector = current_sector->next;
	}
	draw_line(vecdb_to_vec(map_center), \
				vecdb_to_vec(transfo_direc), surf, 0xFF8833);
	fill_pix(surf, map_center.x, map_center.y, 0xFFFF00);
}

int			draw_full_rotmap(SDL_Surface *surf, t_player *player, \
							const t_map *map, SDL_Surface *winsurf)
{
	int ret;

	ret = 0;
	ft_bzero(surf->pixels, surf->h * surf->pitch);
	draw_rot_minimap(surf, player, map);
	draw_border(surf, 0xFFFFFF);
	ret = blit_in_rect(surf, winsurf, ROT_MAP_SHOW);
	return (ret);
}
