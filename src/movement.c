/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/14 13:15:22 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	wall_distance(t_vecdb point, t_wall_node *wall)
{
	double dist;

	dist = (point.x - wall->end_wall.x) * (wall->end_wall.y - wall->start_wall.y) + (point.y - wall->end_wall.y) * (wall->start_wall.x - wall->end_wall.x);
	//could be stored to avoid making long sqrt() operations in real time
	dist /= wall->length;

	return (dist);
}

t_wall_node	*get_deepest_wall(t_vecdb position, t_wall_node *wall, double *min_dist, t_wall_node *tmp_wall)
{
	double dist;
	t_wall_node	*deepest_wall;

	deepest_wall = NULL;
	while (wall != NULL)
	{
		dist = wall_distance(position, wall);
		if (dist < *min_dist && wall != tmp_wall)
		{
			deepest_wall = wall;
			*min_dist = dist;
		}
		wall = wall->next;
	}
	return (deepest_wall);
}

t_vecdb	collide(t_wall_node *wall, double distance, double *col_angle)
{
	t_vecdb	collision;

	collision.x = 0;
	collision.y = 0;
	if (wall == NULL)
		return (collision);
	distance = PLAYER_RADIUS - distance;
	*col_angle = atan2(wall->end_wall.y - wall->start_wall.y, wall->end_wall.x - wall->start_wall.x);
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
	col_angle = atan2(wall->end_wall.y - wall->start_wall.y, wall->end_wall.x - wall->start_wall.x);
	distance = (PLAYER_RADIUS - distance) / sin(col_angle - angle);
	move.x = distance * cos(angle);
	move.y = distance * sin(angle);
	return (move);
}

void	move_player(t_vecdb *position, t_vecdb move, const t_sector_node *sector)
{
	t_wall_node	*tmp_wall;
	double	tmp_distance;
	double	col_angle;

	tmp_wall = NULL;

	position->x += move.x;
	position->y += move.y;
	tmp_distance = PLAYER_RADIUS;
	col_angle = 0;
	tmp_wall = get_deepest_wall(*position, sector->wall_head, &tmp_distance, tmp_wall);
	if (tmp_wall == NULL)
		return ;
	move = collide(tmp_wall, tmp_distance, &col_angle);
	position->x += move.x;
	position->y += move.y;

	tmp_distance = PLAYER_RADIUS;
	tmp_wall = get_deepest_wall(*position, sector->wall_head, &tmp_distance, tmp_wall);
	if (tmp_wall == NULL)
		return ;
	move = move_hyp_length(tmp_wall, tmp_distance, col_angle);
	position->x += move.x;
	position->y += move.y;
}

void	movement(t_player *player, t_vecdb move, const t_sector_node *sector)
{	
	double	movespeed = 0.005;
	t_vecdb	old_position;

	if (fabs(move.x) + fabs(move.y) > 1)
		multvec(&move, 1 / SQRT2);//change later to actually calculate velocity
	move = rotate2d(move, player->angle);
	multvec(&move, movespeed);
	old_position = player->pos;
	move.x += player->inertia.x;
	move.y += player->inertia.y;
	move_player(&player->pos, move, sector);
	//printf("Px:%f\nPy:%f\n", player->pos.x, player->pos.y);
	player->inertia.x = (player->pos.x - old_position.x) * 0.96;
	player->inertia.y = (player->pos.y - old_position.y) * 0.96;
}
