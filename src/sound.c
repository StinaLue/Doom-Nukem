/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:30:36 by afonck            #+#    #+#             */
/*   Updated: 2020/02/10 01:59:26 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	play_katana_sound(t_game *game, t_sdlmain *sdlmain)
{
	t_gamesurfs *gamesurfs;
	t_sound		*sound;
	t_player	*player;

	gamesurfs = &game->surfs;
	sound = &sdlmain->sound;
	player = &game->player;
	if (player->anim == 1 && gamesurfs->current_frame == 0 \
		&& gamesurfs->anim_timer == 0 \
		&& !is_source_playing(sound->source[1]))
	{
		alSourcef(sound->source[1], AL_PITCH, 1.6);
		alSourcei(sound->source[1], AL_BUFFER, sound->buffer[1]);
		alSourcePlay(sound->source[1]);
	}
	else if (player->anim == 0 && gamesurfs->current_frame == 0 \
		&& gamesurfs->anim_timer == 0 \
		&& is_source_playing(sound->source[1]))
		alSourceStop(sound->source[1]);
}

void	play_uzi_sound(t_game *game, t_sdlmain *sdlmain)
{
	t_gamesurfs *gamesurfs;
	t_sound		*sound;
	t_player	*player;

	gamesurfs = &game->surfs;
	sound = &sdlmain->sound;
	player = &game->player;
	if (player->anim == 1 && gamesurfs->current_frame == 0 \
		&& gamesurfs->anim_timer == 0 \
		&& !is_source_playing(sound->source[1]))
	{
		alSourcef(sound->source[1], AL_PITCH, 1);
		alSourcei(sound->source[1], AL_BUFFER, sound->buffer[3]);
		alSourcePlay(sound->source[1]);
	}
	else if (player->anim == 0 && gamesurfs->current_frame == 0 \
			&& gamesurfs->anim_timer == 0 \
			&& is_source_playing(sound->source[1]))
		alSourceStop(sound->source[1]);
}

void	play_weapon_sound(t_game *game, t_sdlmain *sdlmain)
{
	t_gamesurfs *gamesurfs;
	t_sound		*sound;
	t_player	*player;

	gamesurfs = &game->surfs;
	sound = &sdlmain->sound;
	player = &game->player;
	if (player->current_weapon == 0)
		play_katana_sound(game, sdlmain);
	else if (player->current_weapon == 1)
		play_uzi_sound(game, sdlmain);
}

void	play_enemies_sound(t_enemy *enemies, ALuint *buffers, t_map *map)
{
	int i;

	i = 0;
	if (enemies == NULL || map->num_enemies <= 0)
		return ;
	while (i < map->num_enemies)
	{
		if (!is_source_playing(enemies[i].sound_src))
		{
			if (map->enemy_info[i].which_enemy == 0)
				alSourcei(enemies[i].sound_src, AL_BUFFER, buffers[4]);
			else if (map->enemy_info[i].which_enemy == 1)
				alSourcei(enemies[i].sound_src, AL_BUFFER, buffers[5]);
			alSourcePlay(enemies[i].sound_src);
		}
		alSource3f(enemies[i].sound_src, AL_POSITION, \
						enemies[i].pos.x, enemies[i].pos.y, 0);
		i++;
	}
}

int		play_sound(t_game *game, t_sdlmain *sdlmain, t_map *map)
{
	t_gamesurfs *gamesurfs;
	t_sound		*sound;
	t_player	*player;

	gamesurfs = &game->surfs;
	sound = &sdlmain->sound;
	player = &game->player;
	play_weapon_sound(game, sdlmain);
	play_enemies_sound(game->enemy, sound->buffer, map);
	if (player->is_moving == 1 && !is_source_playing(sound->source[2]))
		alSourcePlay(sound->source[2]);
	else if (player->is_moving == 0)
		alSourcePause(sound->source[2]);
	return (0);
}
