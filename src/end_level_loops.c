/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_level_loops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:36:13 by afonck            #+#    #+#             */
/*   Updated: 2020/02/07 16:14:11 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void game_over_loop(t_doom *doom)
{
	t_game		*game;
	t_sdlmain	*sdlmain;

	sdlmain = &(doom->sdlmain);
	game = &(doom->game);
	//SDL_BlitScaled(game->surfs.game_over, NULL, game->surfs.perspective_view, NULL);
	SDL_BlitScaled(game->surfs.game_over, NULL, sdlmain->win_surf, NULL);
	SDL_UpdateWindowSurface(sdlmain->win);
	play_gameover_music(game, sdlmain, doom);
	while (doom->state == GAME_STATE)
	{
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
		{
			check_quit(&sdlmain->event, &doom->state);
			if (sdlmain->event.key.keysym.sym == SDLK_TAB)
				doom->state = EDITOR_STATE;
		}
	}
	soft_reset_player(&game->player, &doom->map);
	/*
	game->player.health = 100;
	game->player.pos = vec_to_vecdb(doom->map.player_spawn);
	doom->game.player.sector = get_sector_by_pos(doom->map.sector_head, \
										doom->game.player.pos);
	if (doom->game.player.pos.x == -1 && doom->game.player.pos.y == -1)
	{
		doom->game.player.sector = doom->map.sector_head;
		doom->game.player.pos = doom->map.sector_head->sector_center;
	}*/
	alSourceStop(sdlmain->sound.source[0]);
	init_source(sdlmain->sound.source[0], 1, 0.3, 1);
	alSourcei(sdlmain->sound.source[0], AL_BUFFER, sdlmain->sound.buffer[0]);
}

void win_loop(t_doom *doom)
{
	t_game		*game;
	t_sdlmain	*sdlmain;

	sdlmain = &(doom->sdlmain);
	game = &(doom->game);
	//SDL_BlitScaled(game->surfs.game_over, NULL, game->surfs.perspective_view, NULL);
	SDL_BlitScaled(game->surfs.victory, NULL, sdlmain->win_surf, NULL);
	SDL_UpdateWindowSurface(sdlmain->win);
	play_win_music(game, sdlmain, doom);
	while (doom->state == GAME_STATE)
	{
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
		{
			check_quit(&sdlmain->event, &doom->state);
			if (sdlmain->event.key.keysym.sym == SDLK_TAB)
				doom->state = EDITOR_STATE;
		}
	}
	soft_reset_player(&game->player, &doom->map);
	/*
	game->player.health = 100;
	doom->game.player.pos = vec_to_vecdb(doom->map.player_spawn);
	doom->game.player.sector = get_sector_by_pos(doom->map.sector_head, \
												doom->game.player.pos);
	if (doom->game.player.pos.x == -1 && doom->game.player.pos.y == -1)
	{
		doom->game.player.sector = doom->map.sector_head;
		doom->game.player.pos = doom->map.sector_head->sector_center;
	}*/
	game->win = 0;
	alSourceStop(sdlmain->sound.source[0]);
	init_source(sdlmain->sound.source[0], 1, 0.3, 1);
	alSourcei(sdlmain->sound.source[0], AL_BUFFER, sdlmain->sound.buffer[0]);
}
