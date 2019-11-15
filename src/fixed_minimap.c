/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:23:32 by phaydont          #+#    #+#             */
/*   Updated: 2019/11/15 16:44:38 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_fixed_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	int i;

	i = 0;
	while (i < NB_WALLS) // looping through each existing wall -> we do the same in print_first_map
	{
		//draw_line(walls[i].start_wall, walls[i].end_wall, surf, 0xFFFFFF);
		draw_line(walls[i].start_wall, walls[i].end_wall, surf, walls[i].color);
		i++;
	}
	draw_line(vecdb_to_vec(player->pos), vecdb_to_vec(player->direc), surf, 0xFF0000);
	fill_pix(surf, player->pos.x, player->pos.y, 0xFFFF00);
}