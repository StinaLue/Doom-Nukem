/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sound_and_ttf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:19:48 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 19:21:10 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	quit_sdl_and_ttf(void)
{
	TTF_Quit();
	SDL_Quit();
}

void	free_sound(t_sound *sound)
{
	alSourcei(sound->source[0], AL_LOOPING, AL_FALSE);
	alSourcei(sound->source[2], AL_LOOPING, AL_FALSE);
	alDeleteSources(NB_SOUND_SOURCES, sound->source);
	alDeleteBuffers(NB_SOUND_BUFFERS, sound->buffer);
	alcDestroyContext(sound->context);
	alcCloseDevice(sound->device);
}

int		free_sdlmain(t_sdlmain *sdlmain)
{
	SDL_DestroyWindow(sdlmain->win);
	sdlmain->win = NULL;
	sdlmain->win_surf = NULL;
	TTF_CloseFont(sdlmain->font);
	sdlmain->font = NULL;
	free_sound(&sdlmain->sound);
	return (EXIT_FAILURE);
}
