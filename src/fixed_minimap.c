/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:23:32 by phaydont          #+#    #+#             */
/*   Updated: 2019/12/11 14:58:22 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	draw_fixed_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	int i;

	i = 0;
	while (i < NB_WALLS) // looping through each existing wall -> we do the same in print_first_map
	{
		//draw_line(walls[i].start_wall, walls[i].end_wall, surf, 0xFFFFFF);
		draw_line(vecdb_to_vec(walls[i].start_wall), vecdb_to_vec(walls[i].end_wall), surf, walls[i].color);
		i++;
	}
	draw_line(vecdb_to_vec(player->pos), vecdb_to_vec(player->direc), surf, 0xFF0000);
	fill_pix(surf, (int)player->pos.x, (int)player->pos.y, 0xFFFF00);
}

int		draw_full_fixedmap(SDL_Surface *surf, t_player *player, t_wall *walls, SDL_Surface *winsurf)
{
	int ret;

	ret = 0;
	ft_bzero(surf->pixels, surf->h * surf->pitch);
	draw_fixed_minimap(surf, player, walls);
	draw_border(surf, 0xFFFFFF);
	if (surf->userdata && ft_strncmp(surf->userdata, "2maps", 5) == 0)
		ret = blit_in_rect(surf, winsurf, FIX_MAP_SHOW + ROT_MAP_SHOW);
	else
		ret = blit_in_rect(surf, winsurf, FIX_MAP_SHOW);
	return (ret);
}
