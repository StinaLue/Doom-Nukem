/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:30:58 by phaydont          #+#    #+#             */
/*   Updated: 2019/11/28 18:08:59 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	movement(t_player *player, t_vecdb move, t_wall *walls)
{	
	double	movespeed = 0.05;

	if (fabs(move.x) + fabs(move.y) == 2)
		move = multvec(move, (1 / SQRT2) * movespeed);
	else
		move = multvec(move, movespeed);
	move = rotate2d(move, player->angle);
	move.x += player->inertia.x;
	move.y += player->inertia.y;
	if (check_collision(player->pos.x + move.x, player->pos.y + move.y, walls) == 0)
	{
		player->pos.x += move.x;
		player->pos.y += move.y;
		player->inertia = multvec(move, 0.9);
	}
	else
	{
		player->inertia.x = 0;
		player->inertia.y = 0;
	}
}