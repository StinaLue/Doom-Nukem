/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:23:32 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/15 12:15:36 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	draw_fixed_minimap(SDL_Surface *surf, t_player *player, const t_map *map)
{
	t_wall_node	*current_wall;
	current_wall = map->sector_head->wall_head;

	while (current_wall != NULL)
	{
		draw_line(vecdb_to_vec(current_wall->start), vecdb_to_vec(current_wall->end), surf, current_wall->color);
		current_wall = current_wall->next;
	}
	draw_line(vecdb_to_vec(player->pos), vecdb_to_vec(player->direc), surf, 0xFF0000);
	fill_pix(surf, (int)player->pos.x, (int)player->pos.y, 0xFFFF00);
}

int		draw_full_fixedmap(SDL_Surface *surf, t_player *player, const t_map *map, SDL_Surface *winsurf)
{
	int ret;

	ret = 0;
	ft_bzero(surf->pixels, surf->h * surf->pitch);
	draw_fixed_minimap(surf, player, map);
	draw_border(surf, 0xFFFFFF);
	if (surf->userdata && ft_strncmp(surf->userdata, "2maps", 5) == 0)
		ret = blit_in_rect(surf, winsurf, FIX_MAP_SHOW + ROT_MAP_SHOW);
	else
		ret = blit_in_rect(surf, winsurf, FIX_MAP_SHOW);
	return (ret);
}
