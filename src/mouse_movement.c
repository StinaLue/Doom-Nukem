/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:40:32 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/07 18:00:32 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	mouse_movement(SDL_MouseMotionEvent event, t_doom *doom)
{
	t_vecdb	move;
	double	angle;

	move.x = event.xrel;
	move.y = (double)event.yrel / 4;
	angle = tan(move.x / doom->sdlmain.win_w);
	doom->game.player.angle -= angle;
	doom->game.player.view_z -= move.y;
}
