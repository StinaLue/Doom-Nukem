/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_level_loops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:36:13 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 16:10:55 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	game_over_loop(t_doom *doom)
{
	t_game		*game;
	t_sdlmain	*sdlmain;

	sdlmain = &(doom->sdlmain);
	game = &(doom->game);
	SDL_BlitScaled(game->surfs.game_over, NULL, sdlmain->win_surf, NULL);
	SDL_UpdateWindowSurface(sdlmain->win);
	play_gameover_music(game, sdlmain, doom);
	while (doom->state == GAME_STATE)
	{
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
		{
			check_quit(&sdlmain->event, &doom->state);
			if (sdlmain->event.key.keysym.sym == SDLK_TAB \
					&& sdlmain->event.type == SDL_KEYDOWN)
				doom->state = EDITOR_STATE;
		}
	}
	soft_reset_player(&game->player, &doom->map);
	alSourceStop(sdlmain->sound.source[0]);
	init_source(sdlmain->sound.source[0], 1, 0.3, 1);
	alSourcei(sdlmain->sound.source[0], AL_BUFFER, sdlmain->sound.buffer[0]);
}

void	win_loop(t_doom *doom)
{
	t_game		*game;
	t_sdlmain	*sdlmain;

	sdlmain = &(doom->sdlmain);
	game = &(doom->game);
	SDL_BlitScaled(game->surfs.victory, NULL, sdlmain->win_surf, NULL);
	SDL_UpdateWindowSurface(sdlmain->win);
	play_win_music(game, sdlmain, doom);
	while (doom->state == GAME_STATE)
	{
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
		{
			check_quit(&sdlmain->event, &doom->state);
			if (sdlmain->event.key.keysym.sym == SDLK_TAB \
				&& sdlmain->event.type == SDL_KEYDOWN)
				doom->state = EDITOR_STATE;
		}
	}
	soft_reset_player(&game->player, &doom->map);
	alSourceStop(sdlmain->sound.source[0]);
	init_source(sdlmain->sound.source[0], 1, 0.3, 1);
	alSourcei(sdlmain->sound.source[0], AL_BUFFER, sdlmain->sound.buffer[0]);
}
