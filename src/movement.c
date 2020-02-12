/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/12 12:13:35 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		teleport(t_player *player)
{
	player->pos = vecdb_add(player->pos, player->move);
	player->move = multvecdb(player->move, 0);
}

void		move_player(t_player *player)
{
	t_wall_node		*tmp1;
	t_wall_node		*tmp2;
	double			tmp_dist;
	double			cang;

	tmp1 = NULL;
	tmp_dist = PLAYER_RADIUS;
	cang = 0;
	if ((tmp1 = find_coll(player, player->sector, &tmp_dist)) != NULL)
	{
		player->move = vecdb_add(player->move, coll(tmp1, tmp_dist, &cang));
		tmp_dist = PLAYER_RADIUS;
		tmp2 = tmp1;
		if ((tmp1 = find_coll(player, player->sector, &tmp_dist)) \
									!= NULL && tmp1 != tmp2)
		{
			player->move = vecdb_add(player->move, acute(tmp1, tmp_dist, cang));
			update_sector(player, player->sector->wall_head);
		}
		if (tmp2 && wall_distance(player->pos, tmp2) < 0)
			teleport(player);
	}
	player->move = vecdb_add(player->move, \
				ccoll(player, player->sector->wall_head));
}

void		movement(t_player *player, t_vecdb move)
{
	if (fabs(move.x) + fabs(move.y) > 1)
		move = multvecdb(move, 1 / M_SQRT2);
	move = rotate2d(move, player->angle);
	move = multvecdb(move, player->movespeed);
	if (player->posz > player->sector->floor_height)
		move = multvecdb(move, 0.5);
	player->move = vecdb_add(move, player->inertia);
	move_player(player);
	player->pos = vecdb_add(player->pos, player->move);
	if (player->posz <= player->sector->floor_height)
		player->inertia = multvecdb(player->move, 0.96);
	else
		player->inertia = multvecdb(player->move, 0.99);
	update_sector(player, player->sector->wall_head);
}

void		update_player(t_player *player)
{
	player->posz += player->zinertia;
	if (player->posz + player->height >= player->sector->ceiling_height)
	{
		player->posz = player->sector->ceiling_height - player->height;
		player->zinertia = 0;
	}
	if (player->posz <= player->sector->floor_height)
	{
		player->posz = player->sector->floor_height;
		player->zinertia = 0;
	}
	if (player->posz > player->sector->floor_height)
		player->zinertia -= 0.016;
}

void		jump(t_player *player)
{
	if (player->posz <= player->sector->floor_height || player->fly)
		player->zinertia = 0.7;
}
