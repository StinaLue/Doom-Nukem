/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:51:05 by afonck            #+#    #+#             */
/*   Updated: 2019/11/21 19:46:05 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	handle_hud(char *hud_flags, SDL_Event *event, const Uint8 *keyboard_state)
{
	//(void)keyboard_state;
	(void)event;
	if (keyboard_state[SDL_SCANCODE_1])
	//if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDL_SCANCODE_1)
	{
		if ((*hud_flags & ROT_MAP_SHOW) == 0)
			*hud_flags |= ROT_MAP_SHOW;
		else
			*hud_flags &= ~(ROT_MAP_SHOW);
	}	
	if (keyboard_state[SDL_SCANCODE_2])
	//if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_2)
	{
		if ((*hud_flags & FIX_MAP_SHOW) == 0)
			*hud_flags |= FIX_MAP_SHOW;
		else
			*hud_flags &= ~(FIX_MAP_SHOW);
	}
}

void	basic_move(t_player *player, t_wall *walls, const Uint8 *keyboard_state)
{
	double pos_x = player->pos.x;
	double pos_y = player->pos.y;
	if (!is_in_map(&player->pos))
	{
		player->pos.x = 70;
		player->pos.y = 70;
	}
	if (keyboard_state[SDL_SCANCODE_UP])
	{
		player->pos.x += cos(player->angle) / 10; // == speed reduction
		player->pos.y += sin(player->angle) / 10;
		if (check_collision(player->pos.x, player->pos.y, walls))
		{
			player->pos.x = pos_x;
			player->pos.y = pos_y;
		}
	}
	if (keyboard_state[SDL_SCANCODE_DOWN])
	{
		player->pos.x -= cos(player->angle) / 10;
		player->pos.y -= sin(player->angle) / 10;
		if (check_collision(player->pos.x, player->pos.y, walls))
		{
			player->pos.x = pos_x;
			player->pos.y = pos_y;
		}
	}
	if (keyboard_state[SDL_SCANCODE_LEFT])
		player->angle -= 0.01;
	if (keyboard_state[SDL_SCANCODE_RIGHT])
		player->angle += 0.01;
	player->direc.x = cos(player->angle) * 5 + player->pos.x;
	player->direc.y = sin(player->angle) * 5 + player->pos.y;
}

void	handle_events(t_doom *doom, t_wall *walls, const Uint8 *keyboard_state)
{
	handle_hud(&doom->data.hud_flags, &doom->sdl.event, keyboard_state);
	basic_move(&doom->player, walls, keyboard_state);
}