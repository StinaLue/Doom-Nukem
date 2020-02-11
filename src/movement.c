/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/11 22:11:25 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		move_player(t_player *player)
{
	t_wall_node		*tmp_wall;
	t_wall_node		*tmp_wall2;
	double			tmp_dist;
	double			col_angle;
	t_vecdb			move;

	tmp_wall = NULL;
	tmp_dist = PLAYER_RADIUS;
	col_angle = 0;
	if ((tmp_wall = get_collision_wall(player, player->sector, &tmp_dist)) \
													!= NULL)
	{
		move = collide(tmp_wall, tmp_dist, &col_angle);
		player->move.x += move.x;
		player->move.y += move.y;
		tmp_dist = PLAYER_RADIUS;
		tmp_wall2 = tmp_wall;
		if ((tmp_wall = get_collision_wall(player, player->sector, &tmp_dist)) \
									!= NULL && tmp_wall != tmp_wall2)
		{
			move = move_hyp_length(tmp_wall, tmp_dist, col_angle);
			player->move.x += move.x;
			player->move.y += move.y;
			update_sector(player, player->sector->wall_head);
		}
		if (tmp_wall2 && wall_distance(player->pos, tmp_wall2) < 0)
		{
			player->pos = vecdb_add(player->pos, player->move);
			player->move = multvecdb(move, 0);
		}
	}
	move = corner_collision(player, player->sector->wall_head);
	player->move.x += move.x;
	player->move.y += move.y;
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
	if (player->posz <= player->sector->floor_height)
		player->zinertia = 0.7;
}
