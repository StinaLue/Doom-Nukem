/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/22 15:09:49 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	wall_distance(t_vecdb point, t_wall_node *wall)
{
	double dist;

	dist = (point.x - wall->end.x) * (wall->end.y - wall->start.y) + (point.y - wall->end.y) * (wall->start.x - wall->end.x);
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

t_wall_node	*get_collision_wall(t_player *player, t_sector_node *sector, double *min_dist, int depth)
{
	double dist;
	t_wall_node	*wall;
	t_wall_node	*deepest_wall;
	t_wall_node	*tmp_deepest_wall;

	if (depth == 0)
		return (NULL);
	wall = sector->wall_head;
	deepest_wall = NULL;
	while (wall != NULL)
	{
		if (is_in_range(player->pos, wall))
		{
			dist = wall_distance(player->pos, wall);
			if (dist < *min_dist)
			{
				if (wall->neighbor_sector == NULL)
				{
					deepest_wall = wall;
					*min_dist = dist;
				}
				else if (wall->neighbor_sector != player->sector)
				{
					tmp_deepest_wall = get_collision_wall(player, wall->neighbor_sector, min_dist, depth - 1);
					if (tmp_deepest_wall != NULL)
						deepest_wall = tmp_deepest_wall;
				}
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
		dist = get_point_distance(player->pos, vec);
		if (dist < PLAYER_RADIUS)
			break ;
		vec = wall->end;
		dist = get_point_distance(player->pos, vec);
		if (dist < PLAYER_RADIUS)
			break ;
		wall = wall->next;
	}
	if (wall == NULL)
		return (move);
	move.x = (player->pos.x - vec.x) / dist * PLAYER_RADIUS - (player->pos.x - vec.x);
	move.y = (player->pos.y - vec.y) / dist * PLAYER_RADIUS - (player->pos.y - vec.y);
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
	*col_angle = atan2(wall->end.y - wall->start.y, wall->end.x - wall->start.x);
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
		if (wall->neighbor_sector != NULL && wall_distance(player->pos, wall) <= 0)
		{
			player->sector = wall->neighbor_sector;
			return ;
		}
		wall = wall->next;
	}
}

void	move_player2(t_player *player)
{
	t_wall_node		*tmp_wall;
	t_wall_node		*tmp_wall2;
	double			tmp_distance;
	double			col_angle;
	t_vecdb			move;

	tmp_wall = NULL;
	tmp_distance = PLAYER_RADIUS;
	col_angle = 0;
	if ((tmp_wall = get_collision_wall(player, player->sector, &tmp_distance, 6)) != NULL)
	{
		move = collide(tmp_wall, tmp_distance, &col_angle);
		player->pos.x += move.x;
		player->pos.y += move.y;
		update_sector(player, player->sector->wall_head);

		tmp_distance = PLAYER_RADIUS;
		tmp_wall2 = tmp_wall;
		if ((tmp_wall = get_collision_wall(player, player->sector, &tmp_distance, 5)) != NULL && tmp_wall != tmp_wall2)
		{
			move = move_hyp_length(tmp_wall, tmp_distance, col_angle);
			player->pos.x += move.x;
			player->pos.y += move.y;
			update_sector(player, player->sector->wall_head);
		}
	}
	move = corner_collision(player, player->sector);
	player->pos.x += move.x;
	player->pos.y += move.y;
	update_sector(player, player->sector->wall_head);
}

void	movement(t_player *player, t_vecdb move)
{
	double	movespeed = 0.005;
	t_vecdb	old_position;

	if (fabs(move.x) + fabs(move.y) > 1)
		move = multvecdb(move, 1 / SQRT2);//change later to actually calculate velocity
	move = rotate2d(move, player->angle);
	move = multvecdb(move, movespeed);

	old_position = player->pos;
	player->pos.x += move.x + player->inertia.x;
	player->pos.y += move.y + player->inertia.y;
	update_sector(player, player->sector->wall_head);
	move_player2(player);
	//printf("Px:%.15f\nPy:%.15f\n", player->pos.x, player->pos.y);
	player->inertia.x = (player->pos.x - old_position.x) * 0.96;
	player->inertia.y = (player->pos.y - old_position.y) * 0.96;
}
