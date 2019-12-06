/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2019/12/06 16:42:03 by phaydont         ###   ########.fr       */
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
	double	offset;
	double	col_angle = 0;

	int		count;
	t_vecdb	origin = {0, 0};
	t_vecdb	A;
	t_vecdb	B;
	t_vecdb	C;
	t_vecdb	P;
	t_vecdb	old_pos = *position;
	(void)old_pos;
	double	col_angle2 = 0;

	position->x += move->x;
	position->y += move->y;
	//can change to this decide wich walls to check collision
	count = 0;
	i = 0;
	while (i < NB_WALLS)
	{
		offset = wall_distance(*position, walls[i].start_wall, walls[i].end_wall);
		if (offset < 0.5)
		{
			if (count)
			{
				
				//attempt to calculate true length of move vector
				offset = 0.5 - offset;
				col_angle2 = atan2(walls[i].end_wall.y - walls[i].start_wall.y, walls[i].end_wall.x - walls[i].start_wall.x) - col_angle;

				B.x = offset * sin(col_angle2);
				B.y = offset * -cos(col_angle2);
				C.x = A.x + B.x;
				C.y = A.y + B.y;
				P = C;
				multvec(&P, dot_product(A, C) / (get_magnitude(origin, A) * get_magnitude(origin, A)));
				C.x = C.x * get_magnitude(origin, A) / get_magnitude(origin, P);
				C.y = C.y * get_magnitude(origin, A) / get_magnitude(origin, P);
				position->x = old_pos.x + C.x;
				position->y = old_pos.y + C.y;
				return ;
			}
			else
			{
				offset = 0.5 - offset;
				col_angle = atan2(walls[i].end_wall.y - walls[i].start_wall.y, walls[i].end_wall.x - walls[i].start_wall.x);

				A.x = offset * sin(col_angle);
				A.y = offset * -cos(col_angle);
				position->x += offset * sin(col_angle);
				position->y += offset * -cos(col_angle);
				count++;
			}
		}
		i++;
	}
}

void	movement(t_player *player, t_vecdb move, t_wall *walls)
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
	move_player(&player->pos, &move, walls);
	printf("Px:%f\nPy:%f\n", player->pos.x, player->pos.y);
	player->inertia.x = (player->pos.x - old_position.x) * 0.9;
	player->inertia.y = (player->pos.y - old_position.y) * 0.9;
	//printf("Ix:%f\nIy:%f\n", player->inertia.x, player->inertia.y);
}