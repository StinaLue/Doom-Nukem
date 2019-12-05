/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2019/12/05 16:40:46 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_side_wall(double pos_x, double pos_y, t_vecdb start_wall, t_vecdb end_wall)
{
	double det = (start_wall.x - end_wall.x) * (start_wall.y - pos_y) - (start_wall.x - pos_x) * (start_wall.y - end_wall.y);
	//printf("%f\n", det);
	if (det < 0) // the lower this number, the bigger the distance between player and collision will be
		return (0);
	else
		return (1);
}

int 	check_collision(double pos_x, double pos_y, t_wall *walls)
{
	int i;
	i = 0;
	while(i < NB_WALLS)//loop through each wall
	{
		if (check_side_wall(pos_x, pos_y, walls[i].start_wall, walls[i].end_wall))
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