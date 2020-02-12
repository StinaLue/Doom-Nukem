/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 02:33:23 by afonck            #+#    #+#             */
/*   Updated: 2020/02/12 02:41:10 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			soft_reset_player(t_player *player, t_map *map)
{
	player->health = 100;
	player->pos = vec_to_vecdb(map->player_spawn);
	player->sector = get_sector_by_pos(map->sector_head, \
										player->pos);
	if (player->pos.x == -1 && player->pos.y == -1 && map->sector_head)
	{
		player->sector = map->sector_head;
		player->pos = map->sector_head->sector_center;
	}
}

int				player_hurt_anim(int health, SDL_Rect *surf_rect)
{
	int y_anim;

	y_anim = 0;
	if (health > 80)
		y_anim = 0;
	else if (health > 60)
		y_anim = surf_rect->h * 1;
	else if (health > 40)
		y_anim = surf_rect->h * 2;
	else if (health > 20)
		y_anim = surf_rect->h * 3;
	else
		y_anim = surf_rect->h * 4;
	return (y_anim);
}
