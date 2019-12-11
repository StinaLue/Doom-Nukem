/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:51:05 by afonck            #+#    #+#             */
/*   Updated: 2019/12/11 15:59:09 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	basic_move(t_player *player, t_wall *walls, const Uint8 *keyboard_state)
{
	t_vecdb	move;
	

	/* if (!is_in_map(&player->pos))
	{
		player->pos.x = 70;
		player->pos.y = 70;
	}*/
	move.x = 0;
	move.y = 0;
	if (keyboard_state[SDL_SCANCODE_W])
		move.y += 1;
	if (keyboard_state[SDL_SCANCODE_S])
		move.y -= 1;
	if (keyboard_state[SDL_SCANCODE_A])
		move.x -= 1;
	if (keyboard_state[SDL_SCANCODE_D])
		move.x += 1;
	movement(player, move, walls);
}

void	basic_look(t_player *player, const Uint8 *keyboard_state)
{
	if (keyboard_state[SDL_SCANCODE_UP])
		player->view_z += 1;
	if (keyboard_state[SDL_SCANCODE_DOWN])
		player->view_z -= 1;
	if (keyboard_state[SDL_SCANCODE_LEFT])
		player->angle += 0.01;
	if (keyboard_state[SDL_SCANCODE_RIGHT])
		player->angle -= 0.01;
	if (keyboard_state[SDL_SCANCODE_PAGEUP])
		player->fov.x++;
	if (keyboard_state[SDL_SCANCODE_PAGEDOWN] && player->fov.x > 1)
		player->fov.x--;
	player->direc.x = sin(player->angle) * -5 + player->pos.x;
	player->direc.y = cos(player->angle) * 5 + player->pos.y;
}

void	handle_keys(t_doom *doom, t_wall *walls, const Uint8 *keyboard_state)
{
	//which order is the right one ?
	basic_look(&doom->player, keyboard_state);
	basic_move(&doom->player, walls, keyboard_state);
}
