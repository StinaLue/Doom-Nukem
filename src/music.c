/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:39:00 by afonck            #+#    #+#             */
/*   Updated: 2020/02/08 02:51:40 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void play_win_music(t_game *game, t_sdlmain *sdlmain, t_doom *doom)
{
	stop_enem_soundsources(game->enemy, doom->map.num_enemies);
	alSourceStopv(NB_SOUND_SOURCES, sdlmain->sound.source);
	init_source(sdlmain->sound.source[0], 1, 1, 1);
	alSourcei(sdlmain->sound.source[0], AL_BUFFER, sdlmain->sound.buffer[8]);
	alSourcePlay(sdlmain->sound.source[0]);
}

void play_gameover_music(t_game *game, t_sdlmain *sdlmain, t_doom *doom)
{
	stop_enem_soundsources(game->enemy, doom->map.num_enemies);
	alSourceStopv(NB_SOUND_SOURCES, sdlmain->sound.source);
	init_source(sdlmain->sound.source[0], 0.8, 1, 1);
	alSourcei(sdlmain->sound.source[0], AL_BUFFER, sdlmain->sound.buffer[7]);
	alSourcePlay(sdlmain->sound.source[0]);
}

void	play_game_music(t_game *game, t_sdlmain *sdlmain, t_doom *doom)
{
	stop_enem_soundsources(game->enemy, doom->map.num_enemies);
	alSourceStopv(NB_SOUND_SOURCES, sdlmain->sound.source);
	if (doom->map.which_music == 0)
	{
		init_source(sdlmain->sound.source[0], 1, 0.3, 1);
		alSourcei(sdlmain->sound.source[0], AL_BUFFER, sdlmain->sound.buffer[0]);
	}
	else if (doom->map.which_music == 1)
	{
		init_source(sdlmain->sound.source[0], 1, 0.3, 1);
		alSourcei(sdlmain->sound.source[0], AL_BUFFER, sdlmain->sound.buffer[10]);
	}
	alSourcePlay(sdlmain->sound.source[0]);
}

void play_editor_music(t_sdlmain *sdlmain, t_doom *doom)
{
	stop_enem_soundsources(doom->game.enemy, doom->map.num_enemies);
	alSourceStopv(NB_SOUND_SOURCES, sdlmain->sound.source);
	init_source(sdlmain->sound.source[0], 1, 1, 1);
	alSourcei(sdlmain->sound.source[0], AL_BUFFER, sdlmain->sound.buffer[9]);
	alSourcePlay(sdlmain->sound.source[0]);
}
