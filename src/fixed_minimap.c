/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:23:32 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/09 17:47:44 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	draw_fixed_minimap(SDL_Surface *surf, \
							t_player *player, const t_map *map)
{
	t_sector_node	*current_sector;
	t_wall_node		*current_wall;

	current_sector = map->sector_head;
	while (current_sector != NULL)
	{
		current_wall = current_sector->wall_head;
		while (current_wall != NULL)
		{
			if (current_wall->neighbor_sector == NULL)
				draw_line(vecdb_to_vec(multvecdb(divvecdb(current_wall->start, MAPMULTIPLIER), 2)), \
					vecdb_to_vec(multvecdb(divvecdb(current_wall->end, MAPMULTIPLIER), 2)), surf, current_wall->color);
			current_wall = current_wall->next;
		}
		current_sector = current_sector->next;
	}
	fill_pix(surf, (int)((player->pos.x / MAPMULTIPLIER) * 2), (int)((player->pos.y / MAPMULTIPLIER) * 2), 0xFFFF00);
}

int		draw_full_fixedmap(SDL_Surface *surf, t_player *player, \
							const t_map *map, SDL_Surface *winsurf)
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
