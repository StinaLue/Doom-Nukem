/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:23:32 by phaydont          #+#    #+#             */
/*   Updated: 2019/11/15 14:01:03 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_fixed_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	int i;
	t_vec playerpos;
	t_vec playerdir;

	i = 0;
	while (i < NB_WALLS) // looping through each existing wall -> we do the same in print_first_map
	{
		//draw_line(walls[i].start_wall, walls[i].end_wall, surf, 0xFFFFFF);
		draw_line(walls[i].start_wall, walls[i].end_wall, surf, walls[i].color);
		i++;
	}
	playerpos.x = player->pos.x;
	playerpos.y = player->pos.y;
	playerdir.x = player->direc.x;
	playerdir.y = player->direc.y;
	draw_line(playerpos, playerdir, surf, 0xFF0000);
	fill_pix(surf, playerpos.x +0.5, playerpos.y +0.5, 0xFFFF00);
}