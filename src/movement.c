/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/08 12:54:27 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	wall_distance(t_vecdb point, t_vecdb a, t_vecdb b)
{
	double dist;

	dist = (point.x - b.x) * (b.y - a.y) + (point.y - b.y) * (a.x - b.x);
	//could be stored to avoid making long sqrt() operations in real time
	dist /= sqrt((b.y - a.y) * (b.y - a.y) + (a.x - b.x) * (a.x - b.x));

	return (dist);
}

void	move_player(t_vecdb *position, t_vecdb *move, const t_sector_node *sector)
{
	t_wall_node	*current_wall;
	double	col_angle;
	double	dist;

	current_wall = sector->wall_head;
	position->x += move->x;
	position->y += move->y;
	while (current_wall != NULL)
	{
		dist = wall_distance(*position, current_wall->start_wall, current_wall->end_wall);
		if (dist < 0.5)
		{
			dist = 0.5000000001 - dist;
			col_angle = atan2(current_wall->start_wall.y - current_wall->end_wall.y, current_wall->start_wall.x - current_wall->end_wall.x);
			position->x += dist * -sin(col_angle);
			position->y += dist * cos(col_angle);
			current_wall = sector->wall_head;
		}
		current_wall = current_wall->next;
	}
	return ;
}

void	movement(t_player *player, t_vecdb move, const t_sector_node *sector)
{	
	double	movespeed = 0.01;
	t_vecdb	old_position;

	if (fabs(move.x) + fabs(move.y) > 1)
		multvec(&move, 1 / SQRT2);//change later to actually calculate velocity
	move = rotate2d(move, player->angle);
	multvec(&move, movespeed);
	old_position = player->pos;
	move.x += player->inertia.x;
	move.y += player->inertia.y;
	move_player(&player->pos, &move, sector);
	//printf("Px:%f\nPy:%f\n", player->pos.x, player->pos.y);
	player->inertia.x = (player->pos.x - old_position.x) * 0.95;
	player->inertia.y = (player->pos.y - old_position.y) * 0.95;
}
