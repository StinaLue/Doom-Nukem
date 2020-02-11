/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_event_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 22:15:41 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 22:18:37 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_quit(SDL_Event *event, int *state)
{
	if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN && \
		event->key.keysym.sym == SDLK_ESCAPE))
		*state = QUIT_STATE;
}

void	check_menu(SDL_Event *event, int *state, \
					int *prev_state_ptr, int prev_state)
{
	if (event->key.keysym.sym == SDLK_TAB)
	{
		*prev_state_ptr = prev_state;
		*state = MENU_STATE;
	}
}

void	check_weapon(SDL_Event *event, t_game *game, int available_weapons)
{
	if (available_weapons == 0)
		return ;
	if (event->key.keysym.sym == SDLK_1 && game->player.current_weapon != 0 \
	&& game->player.anim == 0 && available_weapons == 3)
	{
		game->player.current_weapon = 0;
		game->surfs.anim_timer = 0;
		game->surfs.current_frame = 0;
		game->player.anim = 0;
	}
	else if (event->key.keysym.sym == SDLK_2 \
			&& game->player.current_weapon != 1 \
	&& game->player.anim == 0 && available_weapons == 3)
	{
		game->player.current_weapon = 1;
		game->surfs.anim_timer = 0;
		game->surfs.current_frame = 0;
		game->player.anim = 0;
	}
}

void	check_anim(t_game *game)
{
	if (game->surfs.current_frame == 0)
	{
		if (game->player.anim == 1)
			game->player.anim = 0;
		else
			game->player.anim = 1;
	}
}
