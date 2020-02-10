/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openal_sub_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:47:16 by afonck            #+#    #+#             */
/*   Updated: 2020/02/10 01:47:54 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "al.h"

int		is_buffer_playing(ALuint src, ALuint buffer)
{
	ALint playing_buffer;

	alGetSourcei(src, AL_BUFFER, &playing_buffer);
	return ((ALuint)playing_buffer == buffer);
}

void	init_source(ALuint src, ALfloat pitch, ALfloat gain, int loop)
{
	alSourcef(src, AL_PITCH, pitch);
	alSourcef(src, AL_GAIN, gain);
	alSource3f(src, AL_POSITION, 0, 0, 0);
	alSource3f(src, AL_VELOCITY, 0, 0, 0);
	alSourcei(src, AL_LOOPING, loop);
}

int		is_source_playing(ALuint source)
{
	ALenum state;

	alGetSourcei(source, AL_SOURCE_STATE, &state);
	return (state == AL_PLAYING);
}
