/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:12:00 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 19:13:54 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		load_sounds(t_sound *sound)
{
	if ((load_wav("assets/sounds/beet.wav", sound->buffer[0])) != 0)
		return (error_return("error loading %{r}s\n", "beet.wav"));
	if ((load_wav("assets/sounds/niceswordsound.wav", sound->buffer[1])) != 0)
		return (error_return("error loading %{r}s\n", "niceswordsound.wav"));
	if ((load_wav("assets/sounds/footsteps-1.wav", sound->buffer[2])) != 0)
		return (error_return("error loading %{r}s\n", "footsteps-1.wav"));
	if ((load_wav("assets/sounds/uzi.wav", sound->buffer[3])) != 0)
		return (error_return("error loading %{r}s\n", "uzi.wav"));
	if ((load_wav("assets/sounds/zombie_mono.wav", sound->buffer[4])) != 0)
		return (error_return("error loading %{r}s\n", "zombie.wav"));
	if ((load_wav("assets/sounds/boss.wav", sound->buffer[5])) != 0)
		return (error_return("error loading %{r}s\n", "boss.wav"));
	if ((load_wav("assets/sounds/boss_hit.wav", sound->buffer[6])) != 0)
		return (error_return("error loading %{r}s\n", "boss_hit.wav"));
	if ((load_wav("assets/sounds/you_lose.wav", sound->buffer[7])) != 0)
		return (error_return("error loading %{r}s\n", "you_lose.wav"));
	if ((load_wav("assets/sounds/win.wav", sound->buffer[8])) != 0)
		return (error_return("error loading %{r}s\n", "win.wav"));
	if ((load_wav("assets/sounds/chill_music.wav", sound->buffer[9])) != 0)
		return (error_return("error loading %{r}s\n", "chill_music.wav"));
	if ((load_wav("assets/sounds/doom_theme.wav", sound->buffer[10])) != 0)
		return (error_return("error loading %{r}s\n", "doom_theme.wav"));
	return (0);
}

int		init_sound(t_sound *sound)
{
	if ((sound->device = alcOpenDevice(NULL)) == NULL)
		return (1);
	if ((sound->context = alcCreateContext(sound->device, NULL)) == NULL)
		return (1);
	alcMakeContextCurrent(sound->context);
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alGenSources(NB_SOUND_SOURCES, sound->source);
	init_source(sound->source[0], 1, 0.3, 1);
	init_source(sound->source[1], 1, 1, 0);
	init_source(sound->source[2], 1.5, 1, 1);
	alGetError();
	alGenBuffers(NB_SOUND_BUFFERS, sound->buffer);
	if (load_sounds(sound) != 0)
		return (1);
	alSourcei(sound->source[2], AL_BUFFER, sound->buffer[2]);
	return (0);
}
