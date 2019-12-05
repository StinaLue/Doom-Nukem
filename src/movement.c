/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2019/12/05 17:06:57 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_side_wall(t_vecdb c, t_vecdb a, t_vecdb b)
{
	double dist;
	//double det = (start_wall.x - end_wall.x) * (start_wall.y - pos_y) - (start_wall.x - pos_x) * (start_wall.y - end_wall.y);
	//printf("%f\n", det);
	dist = (c.x - a.x) * (a.y - b.y) + (c.y - a.y) * (b.x - a.x);
	dist /= sqrt((a.y - b.y) * (a.y - b.y) + (b.x - a.x) * (b.x- a.x));
	if (dist < -3) // the lower this number, the bigger the distance between player and collision will be
		return (0);
	else
		return (1);
}

int 	check_collision(double pos_x, double pos_y, t_wall *walls)
{
	t_vecdb point;
	int i;

	point.x = pos_x;
	point.y = pos_y;
	i = 0;
	while(i < NB_WALLS)//loop through each wall
	{
		if (check_side_wall(point, walls[i].start_wall, walls[i].end_wall))
			return (1);
		i++;
	}
	return (0);
}

void	movement(t_player *player, t_vecdb move, t_wall *walls)
{	
	double	movespeed = 0.01;

	if (fabs(move.x) + fabs(move.y) > 1)
		multvec(&move, 1 / SQRT2);//change later to actually calculate velocity
	move = rotate2d(move, player->angle);
	multvec(&move, movespeed);
	move.x += player->inertia.x;
	move.y += player->inertia.y;
	//printf("==x movement==\n");
	if (check_collision(player->pos.x, player->pos.y + move.y, walls) == 0)
	{
		player->pos.y += move.y;
		player->inertia.y = 0.9 *move.y;
	}
	else
		player->inertia.y = 0;
	//printf("==y movement==\n");
	if (check_collision(player->pos.x + move.x, player->pos.y, walls) == 0)
	{
		player->pos.x += move.x;
		player->inertia.x = 0.9 *move.x;
	}
	else
		player->inertia.x = 0;
}