/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_surroundings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 22:05:27 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 22:06:11 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vecdb		move_hyp_length(t_wall_node *wall, double distance, double angle)
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

void		update_sector(t_player *player, t_wall_node *wall)
{
	while (wall != NULL)
	{
		if (wall->neighbor_sector != NULL \
			&& is_in_direction(player->move, wall) \
			&& is_in_range(vecdb_add(player->pos, player->move), wall) \
			&& wall_distance(player->pos, wall) <= 0)
		{
			player->sector = wall->neighbor_sector;
			return ;
		}
		wall = wall->next;
	}
}

double		wall_distance(t_vecdb point, t_wall_node *wall)
{
	double dist;

	dist = (point.x - wall->end.x) * (wall->end.y - wall->start.y) \
			+ (point.y - wall->end.y) * (wall->start.x - wall->end.x);
	dist /= wall->length;
	return (dist);
}

int			is_in_range(t_vecdb pos, t_wall_node *wall)
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

int			is_in_direction(t_vecdb move, t_wall_node *wall)
{
	t_vecdb wall_vec;

	wall_vec = vecdb_diff(wall->end, wall->start);
	if (cross_product(wall_vec, move) > 0)
		return (1);
	return (0);
}
