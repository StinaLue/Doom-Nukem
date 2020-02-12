/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_collisions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:50:01 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/12 12:53:30 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			portal_collide(t_player *player, t_sector_node *sector)
{
	if (player->posz + KNEE_HEIGHT < sector->floor_height)
		return (1);
	if (player->posz + player->height > sector->ceiling_height)
		return (1);
	if (player->height > sector->ceiling_height - sector->floor_height)
		return (1);
	return (0);
}

int			set_deepest(t_wall_node *wall, t_wall_node **deepest_wall, \
				t_player *player, double *min_dist)
{
	t_wall_node	*tmp_deepest_wall;

	if (wall->neighbor_sector != NULL && \
		!portal_collide(player, wall->neighbor_sector) && wall->wall_type == 1)
	{
		tmp_deepest_wall = find_coll(player, wall->neighbor_sector, min_dist);
		if (tmp_deepest_wall != NULL)
			*deepest_wall = tmp_deepest_wall;
		return (1);
	}
	return (0);
}

t_wall_node	*find_coll(t_player *player, \
				t_sector_node *sector, double *min_dist)
{
	double		dist;
	t_wall_node	*wall;
	t_wall_node	*deepest_wall;

	wall = sector->wall_head;
	deepest_wall = NULL;
	while (wall != NULL)
	{
		if (in_dir(player->move, wall) && \
					in_r(vecdb_add(player->pos, player->move), wall))
		{
			dist = wall_distance(vecdb_add(player->pos, player->move), wall);
			if (dist < *min_dist)
			{
				if (!set_deepest(wall, &deepest_wall, player, min_dist))
				{
					deepest_wall = wall;
					*min_dist = dist;
				}
			}
		}
		wall = wall->next;
	}
	return (deepest_wall);
}

t_vecdb		ccoll(t_player *player, t_wall_node *wall)
{
	double		dist;
	t_vecdb		vec;
	t_vecdb		move;

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
	return (move);
}

t_vecdb		coll(t_wall_node *wall, double distance, double *col_angle)
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
