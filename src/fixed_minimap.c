/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:23:32 by phaydont          #+#    #+#             */
/*   Updated: 2019/11/26 22:00:06 by afonck           ###   ########.fr       */
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

void	draw_full_fixedmap(SDL_Surface *surf, t_player *player, t_wall *walls, SDL_Surface *winsurf)
{
	t_vec topleft_fixedmap;
	t_vec topright_fixedmap;
	t_vec bottomleft_fixedmap;
	t_vec bottomright_fixedmap;

	ft_bzero(surf->pixels, surf->h * surf->pitch);
	give_vec_values(&topleft_fixedmap, 0, 0);
	give_vec_values(&topright_fixedmap, FIXED_MAP_WIDTH - 1, 0);
	give_vec_values(&bottomleft_fixedmap, 0, FIXED_MAP_HEIGHT - 1);
	give_vec_values(&bottomright_fixedmap, FIXED_MAP_WIDTH - 1, FIXED_MAP_HEIGHT - 1);
	draw_fixed_minimap(surf, player, walls);
	draw_line(topleft_fixedmap, topright_fixedmap, surf, 0xFFFFFF);
	draw_line(bottomleft_fixedmap, bottomright_fixedmap, surf, 0xFFFFFF);
	draw_line(topleft_fixedmap, bottomleft_fixedmap, surf, 0xFFFFFF);
	draw_line(topright_fixedmap, bottomright_fixedmap, surf, 0xFFFFFF);
	if (surf->userdata && ft_strncmp(surf->userdata, "2maps", 5) == 0)
		blit_in_rect(surf, winsurf, FIX_MAP_SHOW + ROT_MAP_SHOW);
	else
		blit_in_rect(surf, winsurf, FIX_MAP_SHOW);
}
