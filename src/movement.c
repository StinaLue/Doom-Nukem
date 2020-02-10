/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/10 14:45:48 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	wall_distance(t_vecdb point, t_wall_node *wall)
{
	double dist;

	dist = (point.x - wall->end.x) * (wall->end.y - wall->start.y) \
			+ (point.y - wall->end.y) * (wall->start.x - wall->end.x);
	dist /= wall->length;
	return (dist);
}

int		is_in_range(t_vecdb pos, t_wall_node *wall)
{
	t_vecdb tmp_wall;
	t_vecdb tmp_pos;

	tmp_wall.x = wall->start.x - wall->end.x;
	tmp_wall.y = wall->start.y - wall->end.y;
	tmp_pos.x = pos.x - wall->end.x;
	tmp_pos.y = pos.y - wall->end.y;
	if (dot_product(tmp_wall, tmp_pos) < 0)
		return (0);
	tmp_wall.x = wall->end.x - wall->start.x;
	tmp_wall.y = wall->end.y - wall->start.y;
	tmp_pos.x = pos.x - wall->start.x;
	tmp_pos.y = pos.y - wall->start.y;
	if (dot_product(tmp_wall, tmp_pos) < 0)
		return (0);
	return (1);
}

int		is_in_direction(t_vecdb move, t_wall_node *wall)
{
	t_vecdb wall_vec;

	wall_vec = vecdb_diff(wall->end, wall->start);

	if (cross_product(wall_vec, move) > 0)
		return (1);
	return (0);
}

t_wall_node	*get_collision_wall(t_player *player, \
				t_sector_node *sector, double *min_dist)
{
	double dist;
	t_wall_node	*wall;
	t_wall_node	*deepest_wall;
	t_wall_node	*tmp_deepest_wall;

	wall = sector->wall_head;
	deepest_wall = NULL;
	while (wall != NULL)
	{
		if (is_in_direction(player->move, wall) \
					&& is_in_range(vecdb_add(player->pos, player->move), wall))
		{
			dist = wall_distance(vecdb_add(player->pos, player->move), wall);
			if (dist < *min_dist)
			{
				if (wall->neighbor_sector != NULL && wall->wall_type == 1)
				{
					tmp_deepest_wall = \
							get_collision_wall(player, wall->neighbor_sector, min_dist);
					if (tmp_deepest_wall != NULL)
						deepest_wall = tmp_deepest_wall;
				}
				else
				{
					deepest_wall = wall;
					*min_dist = dist;
				}
				/*
				if (wall->neighbor_sector == NULL)
				{
					deepest_wall = wall;
					*min_dist = dist;
				}
				else
				{
					tmp_deepest_wall = get_collision_wall(player, wall->neighbor_sector, min_dist);
					if (tmp_deepest_wall != NULL)
						deepest_wall = tmp_deepest_wall;
				}*/
			}
		}
		wall = wall->next;
	}
	return (deepest_wall);
}

t_vecdb	corner_collision(t_player *player, t_sector_node *sector)
{
	t_wall_node	*wall;
	double		dist;
	t_vecdb		vec;
	t_vecdb		move;

	wall = sector->wall_head;
	move.x = 0;
	move.y = 0;
	while (wall != NULL)
	{
		vec = wall->start;
		dist = get_point_distance(vecdb_add(player->pos, player->move), vec);
		if (dist < PLAYER_RADIUS)
			break ;
		vec = wall->end;
		dist = get_point_distance(vecdb_add(player->pos, player->move), vec);
		if (dist < PLAYER_RADIUS)
			break ;
		wall = wall->next;
	}
	if (wall == NULL)
		return (move);
	move.x = (player->pos.x + player->move.x - vec.x) / dist * PLAYER_RADIUS \
				- (player->pos.x + player->move.x - vec.x);
	move.y = (player->pos.y + player->move.y - vec.y) / dist * PLAYER_RADIUS \
				- (player->pos.y + player->move.y - vec.y);
	//move = vecdb_diff(multvecdb(vecdb_add(player->pos, player->move), 1 / dist * PLAYER_RADIUS), vecdb_diff(vecdb_add(player->pos, player->move), vec));
	return (move);
}

t_vecdb	collide(t_wall_node *wall, double distance, double *col_angle)
{
	t_vecdb	collision;

	collision.x = 0;
	collision.y = 0;
	if (wall == NULL)
		return (collision);
	distance = PLAYER_RADIUS - distance;
	*col_angle = atan2(wall->end.y - wall->start.y, \
						wall->end.x - wall->start.x);
	collision.x = distance * sin(*col_angle);
	collision.y = distance * -cos(*col_angle);
	return (collision);
}

t_vecdb	move_hyp_length(t_wall_node *wall, double distance, double angle)
{
	double	col_angle;
	t_vecdb	move;

	move.x = 0;
	move.y = 0;
	if (wall == NULL)
		return (move);
	col_angle = atan2(wall->end.y - wall->start.y, wall->end.x - wall->start.x);
	distance = (PLAYER_RADIUS - distance) / sin(col_angle - angle);
	move.x = distance * cos(angle);
	move.y = distance * sin(angle);
	return (move);
}

void	update_sector(t_player *player, t_wall_node *wall)
{
	while (wall != NULL)
	{
		if (wall->neighbor_sector != NULL \
			&& is_in_direction(player->move, wall) \
			&& is_in_range(vecdb_add(player->pos, player->move), wall) \
			&& wall_distance(player->pos, wall) <= 0)
		{
			player->sector = wall->neighbor_sector;
			player->posz = player->sector->floor_height;
			return ;
		}
		wall = wall->next;
	}
}

void	move_player(t_player *player)
{
	t_wall_node		*tmp_wall;
	t_wall_node		*tmp_wall2;
	double			tmp_dist;
	double			col_angle;
	t_vecdb			move;

	tmp_wall = NULL;
	tmp_dist = PLAYER_RADIUS;
	col_angle = 0;
	if ((tmp_wall = get_collision_wall(player, player->sector, &tmp_dist)) != NULL)
	{
		move = collide(tmp_wall, tmp_dist, &col_angle);
		player->move.x += move.x;
		player->move.y += move.y;
		//update_sector(player, player->sector->wall_head);
		tmp_dist = PLAYER_RADIUS;
		tmp_wall2 = tmp_wall;
		if ((tmp_wall = get_collision_wall(player, player->sector, &tmp_dist)) != NULL && tmp_wall != tmp_wall2)
		{
			move = move_hyp_length(tmp_wall, tmp_dist, col_angle);
			player->move.x += move.x;
			player->move.y += move.y;
			//update_sector(player, player->sector->wall_head);
		}
		if (tmp_wall2 && wall_distance(player->pos, tmp_wall2) < 0)
		{
			player->pos = vecdb_add(player->pos, player->move);
			player->move = multvecdb(move, 0);
		}
	}
	move = corner_collision(player, player->sector);
	player->move.x += move.x;
	player->move.y += move.y;
	//update_sector(player, player->sector->wall_head);
}

void	movement(t_player *player, t_vecdb move)
{
	if (fabs(move.x) + fabs(move.y) > 1)
		move = multvecdb(move, 1 / SQRT2);//change later to actually calculate velocity
	move = rotate2d(move, player->angle);
	move = multvecdb(move, player->movespeed);
	player->move = vecdb_add(move, player->inertia);
	//update_sector(player, player->sector->wall_head);
	move_player(player);
	player->pos = vecdb_add(player->pos, player->move);
	player->inertia = multvecdb(player->move, 0.96);
	update_sector(player, player->sector->wall_head);
	player->posz = player->sector->floor_height;
}
