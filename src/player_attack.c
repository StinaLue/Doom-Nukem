/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_attack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 02:38:54 by afonck            #+#    #+#             */
/*   Updated: 2020/02/12 03:28:45 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


void    check_hit_uzi(int num_enemies, int *is_enemy_hit, \
        t_vecdb dir_player, t_enemy *enemy)
{
	int i;

	i = 0;
	while (i < num_enemies && *is_enemy_hit == 0)
	{
		if (get_point_distance(dir_player, enemy[i].pos) < 22)
		{
			enemy[i].health -= 1;
			*is_enemy_hit = 1;
		}
		i++;
	}
}

void    raycast_uzi(t_player *player, \
								t_enemy *enemy, int num_enemies)
{
	int		is_enemy_hit;
	t_vecdb	dir_player;
	int		nb_steps;
	t_vecdb	step;

	nb_steps = 0;
	is_enemy_hit = 0;
	dir_player.x = -sin(player->angle) * 2 + player->pos.x;
	dir_player.y = cos(player->angle) * 2 + player->pos.y;
	step = vecdb_diff(dir_player, player->pos);
	while (nb_steps < 100 && is_enemy_hit == 0)
	{
		check_hit_uzi(num_enemies, &is_enemy_hit, dir_player, enemy);
		dir_player = vecdb_add(dir_player, step);
		nb_steps++;
	}
}

void	katana_hit(t_player *player, t_enemy *enemy, int num_enemies)
{
	int i;

	i = 0;
	while (i < num_enemies)
	{
		if (get_point_distance(player->pos, enemy[i].pos) < 22)
			enemy[i].health -= 1;
		i++;
	}
}

int     player_attack(t_enemy *enemy, \
					t_player *player, t_map *map, t_gamesurfs *surfs)
{
	if (player->current_weapon == 0 && player->anim == 1 \
        && surfs->current_frame == 3)
	{
		katana_hit(player, enemy, map->num_enemies);
	}
	else if (player->current_weapon == 1 \
			&& player->anim == 1 && surfs->current_frame == 2)
	{
		raycast_uzi(player, enemy, map->num_enemies);
	}
	set_listener_ori(player->angle, player->pos);
	return (0);
}
