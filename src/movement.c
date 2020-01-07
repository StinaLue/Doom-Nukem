/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/07 16:22:20 by phaydont         ###   ########.fr       */
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

void	check_second_collision(t_vecdb *position, double col_angle, int i, const t_sector *sector)
{
	double dist;
	double col_angle2;

	if (i >= sector->num_walls)
		i = 0;
	else if (i < 0)
		i = sector->num_walls - 1;

	if ((dist = wall_distance(*position, sector->walls[i].start_wall, sector->walls[i].end_wall)) >= 0.5)
		return ;
	dist = 0.5 - dist;
	col_angle2 = atan2(sector->walls[i].start_wall.y - sector->walls[i].end_wall.y, sector->walls[i].start_wall.x - sector->walls[i].end_wall.x);
	col_angle2 = col_angle - col_angle2;
	dist = dist / sin(col_angle2);
	position->x += dist * cos(col_angle);
	position->y += dist * sin(col_angle);

}

void	move_player(t_vecdb *position, t_vecdb *move, const t_sector_node *sector)
{
	t_wall_node	*current_wall;
	current_wall = sector->wall_head;

	position->x += move->x;
	while (current_wall != NULL)
	{
		if (wall_distance(*position, current_wall->start_wall, current_wall->end_wall) < 0.5)
		{
			position->x -= move->x;
			return ;
		}
		current_wall = current_wall->next;
	}

	position->y += move->y;
	while (current_wall != NULL)
	{
		if (wall_distance(*position, current_wall->start_wall, current_wall->end_wall) < 0.5)
		{
			position->y -= move->y;
			return ;
		}
		current_wall = current_wall->next;
	}


	/*
	int		i;
	double	dist;
	double	smallest_dist;
	int		iw;
	double	col_angle;

	position->x += move->x;
	position->y += move->y;
	i = -1;
	smallest_dist = 0.5;
	iw = -1;
	while (++i < sector->num_walls)
	{
		dist = wall_distance(*position, sector->walls[i].start_wall, sector->walls[i].end_wall);
		if (dist < smallest_dist)
		{
			iw = i;
			smallest_dist = dist;
		}
	}
	if (iw == -1)
		return ;
	dist = 0.5 - smallest_dist;
	col_angle = atan2(sector->walls[iw].start_wall.y - sector->walls[iw].end_wall.y, sector->walls[iw].start_wall.x - sector->walls[iw].end_wall.x);
	position->x += dist * -sin(col_angle);
	position->y += dist * cos(col_angle);
	if (iw >= 0)
	{
		check_second_collision(position, col_angle, iw - 1, sector);
		check_second_collision(position, col_angle, iw + 1, sector);
	}*/
}

void	movement(t_player *player, t_vecdb move, const t_sector_node *sector)
{	
	double	movespeed = 0.006;
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
