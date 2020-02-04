/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:51:05 by afonck            #+#    #+#             */
/*   Updated: 2020/02/04 16:34:55 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	basic_move(t_player *player, const Uint8 *keyboard_state)//, t_sound *sound)
{
	t_vecdb	move;

	move.x = 0;
	move.y = 0;
	if (keyboard_state[SDL_SCANCODE_W])
		move.y +=1;
	if (keyboard_state[SDL_SCANCODE_S])
		move.y -= 1;
	if (keyboard_state[SDL_SCANCODE_A])
		move.x -= 1;
	if (keyboard_state[SDL_SCANCODE_D])
		move.x += 1;
	if (player->is_moving == 0 && (move.x != 0 || move.y != 0))
	{
		player->is_moving = 1;
		//alSourcePlay(sound->source[2]);
	}
	else if (move.x == 0 && move.y == 0)
	{
		player->is_moving = 0;
		//alSourcePause(sound->source[2]);
	}
	movement(player, move);
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
	if (keyboard_state[SDL_SCANCODE_PAGEUP] && player->true_fov > 1.06)//hardcoded 60deg
		player->true_fov -= 0.01;
	if (keyboard_state[SDL_SCANCODE_PAGEDOWN] && player->true_fov < 2.27)//hardcoded 130deg
		player->true_fov += 0.01;
	player->fov.x = 100 * sin(player->true_fov / 2);
	player->fov.y = 100 * cos(player->true_fov / 2);
	/*if (keyboard_state[SDL_SCANCODE_H])
		player->helper = 1;
	else
		player->helper = 0;*/
}

void	handle_keys(t_doom *doom, const Uint8 *keyboard_state)//, t_sound *sound)
{
	basic_look(&doom->game.player, keyboard_state);
	basic_move(&doom->game.player, keyboard_state);//, sound);
}
