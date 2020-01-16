/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:22:14 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/16 14:54:10 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	init_rotate_wall(t_wall *new_wall, const t_wall_node *current_wall, const t_player *player)
{
	new_wall->start.x = current_wall->start.x - player->pos.x;
	new_wall->start.y = current_wall->start.y - player->pos.y;
	new_wall->end.x = current_wall->end.x - player->pos.x;
	new_wall->end.y = current_wall->end.y - player->pos.y;
	new_wall->start = rotate2d(new_wall->start, -player->angle);
	new_wall->end = rotate2d(new_wall->end, -player->angle);
}

void	draw_rot_minimap(SDL_Surface *surf, t_player *player, const t_map *map)
{
	t_wall transfo_wall;
	t_wall wall_tmp;
	t_vecdb map_center;
	t_vecdb transfo_direc;
	t_wall_node *current_wall;
	t_sector_node *current_sector;
	
	map_center.x = surf->w / 2 +0.5;
	map_center.y = surf->h / 2 +0.5;
	transfo_direc.x = player->inertia.x * 100;
	transfo_direc.y = player->inertia.y * 100;
	transfo_direc = rotate2d(transfo_direc, -player->angle);
	transfo_direc.x = map_center.x + transfo_direc.x;
	transfo_direc.y = map_center.y + transfo_direc.y;

	current_sector = map->sector_head;
	while (current_sector != NULL)
	{
		current_wall = current_sector->wall_head;
		while (current_wall != NULL)
		{
			if (current_wall->neighbor_sector == -1)
			{
				init_rotate_wall(&wall_tmp, current_wall, player);
				transfo_wall.start.x = map_center.x + wall_tmp.start.x;
				transfo_wall.start.y = map_center.y + wall_tmp.start.y;
				transfo_wall.end.x = map_center.x + wall_tmp.end.x;
				transfo_wall.end.y = map_center.y + wall_tmp.end.y;
				draw_line(vecdb_to_vec(transfo_wall.start), vecdb_to_vec(transfo_wall.end), surf, current_wall->color);
			}
			current_wall = current_wall->next;
		}
		current_sector = current_sector->next;
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
