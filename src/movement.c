/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2019/12/05 20:17:39 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		collision(t_vecdb point, t_vecdb b, t_vecdb a, double distance)
{
	double dist;

	dist = (point.x - a.x) * (a.y - b.y) + (point.y - a.y) * (b.x - a.x);
	printf("wat:%f\n", dist);
	dist /= sqrt((a.y - b.y) * (a.y - b.y) + (b.x - a.x) * (b.x - a.x));
	printf("mur dist:%f\n", dist);
	if (dist < distance)
		return (1);
	else
		return (0);
}

int		try_move(t_vecdb position, t_vecdb move, t_wall *walls)
{
	int		i;

	position.y += move.y;
	position.x += move.x;
	i = 0;

	while (i < NB_WALLS)
	{
		//can change to this decide wich walls to check collision
		if (collision(position, walls[i].start_wall, walls[i].end_wall, 1.0))
		{
			//can change this to calculate actual new velocity
			return (0);
		}
		i++;
	}
	return (1);
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

	if (try_move(player->pos, move, walls))
	{
		player->pos.y += move.y;
		player->pos.x += move.x;
		multvec(&move, 0.9);
		player->inertia = move;
	}
	else
	{
		player->inertia.x = 0;
		player->inertia.y = 0;
	}
}