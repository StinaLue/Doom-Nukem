/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2019/12/09 17:47:16 by phaydont         ###   ########.fr       */
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

void	move_player(t_vecdb *position, t_vecdb *move, t_wall *walls)
{
	int		i;
	double	dist;
	double	col_angle = 0;
	int		count;
	t_vecdb	A;
	double	col_angle2 = 0;
	int	save = -1;

	position->x += move->x;
	position->y += move->y;
	count = 0;
	i = 0;
	//calculer l'angle directement de la perpendiculaire...
	while (i < NB_WALLS)
	{
		if (i == save)
		{
			i++;
			continue ;
		}
		
		dist = wall_distance(*position, walls[i].start_wall, walls[i].end_wall);
		if (dist < 0.5)
		{
			if (count == 1)
			{
				dist = 0.5 - dist;
				col_angle2 = atan2(walls[i].start_wall.y - walls[i].end_wall.y, walls[i].start_wall.x - walls[i].end_wall.x);
				col_angle2 = col_angle - col_angle2;
				dist = dist / sin(col_angle2);
				position->x += dist * cos(col_angle);
				position->y += dist * sin(col_angle);
				return ;
			}
			else
			{
				dist = 0.5 - dist;
				col_angle = atan2(walls[i].start_wall.y - walls[i].end_wall.y, walls[i].start_wall.x - walls[i].end_wall.x);
				A.x = dist * -sin(col_angle);
				A.y = dist * cos(col_angle);
				position->x += dist * -sin(col_angle);
				position->y += dist * cos(col_angle);
				save = i;
				i = 0;
				count = 1;
				continue ;
			}
		}
		i++;
	}
}

void	movement(t_player *player, t_vecdb move, t_wall *walls)
{	
	double	movespeed = 0.02;
	t_vecdb	old_position;

	if (fabs(move.x) + fabs(move.y) > 1)
		multvec(&move, 1 / SQRT2);//change later to actually calculate velocity
	move = rotate2d(move, player->angle);
	multvec(&move, movespeed);
	old_position = player->pos;
	move.x += player->inertia.x;
	move.y += player->inertia.y;
	move_player(&player->pos, &move, walls);
	//printf("Px:%f\nPy:%f\n", player->pos.x, player->pos.y);
	player->inertia.x = (player->pos.x - old_position.x) * 0.9;
	player->inertia.y = (player->pos.y - old_position.y) * 0.9;
}