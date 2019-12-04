/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2019/12/03 12:16:45 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	movement(t_player *player, t_vecdb move, t_wall *walls)
{	
	double	movespeed = 0.01;

	if (fabs(move.x) + fabs(move.y) > 1)
		move = multvec(move, 1 / SQRT2);//change later to actually calculate velocity
	move = rotate2d(move, player->angle);
	move = multvec(move, movespeed);
	move.x += player->inertia.x;
	move.y += player->inertia.y;
	if (check_collision(player->pos.x + move.x, player->pos.y, walls) == 0)
	{
		player->pos.x += move.x;
		player->inertia.x = 0.9 *move.x;
	}
	else
		player->inertia.x = 0;
	if (check_collision(player->pos.x, player->pos.y + move.y, walls) == 0)
	{
		player->pos.y += move.y;
		player->inertia.y = 0.9 *move.y;
	}
	else
		player->inertia.y = 0;
}