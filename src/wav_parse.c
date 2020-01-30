/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wav_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 00:15:56 by afonck            #+#    #+#             */
/*   Updated: 2020/01/31 00:25:58 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "al.h"
#include "libft.h"
//#include "libwav.h"

static int error_return(char *s1, char *s2)
{
    if (s1 && s2)
        ft_dprintf(STDERR_FILENO, s1, s2);
    else
        ft_dprintf(STDERR_FILENO, s1);
    return (1);
}

ALenum GetFormatFromInfo(short channels, short bitsPerSample)
{
	bitsPerSample = 0;
	if (channels == 1)
		return AL_FORMAT_MONO16;
	return AL_FORMAT_STEREO16;
}

void	endian_swap_short(short *x)
{
	*x = (*x>>8) | (*x<<8);
}

void	endian_swap_int(int *x)
{
	*x = (*x>>24) | 
        ((*x<<8) & 0x00FF0000) |
        ((*x>>8) & 0x0000FF00) |
        (*x<<24);
}

void file_ignore_bytes(int fd, short extraParams)
{
	char buf[1];

	while (extraParams > 0)
	{
		read(fd, buf, 1);
		extraParams--;
	}
}

int	loadWAV(char *file, ALuint buffer)
{
	int		fd;
	char	xbuffer[5];
	short audioFormat;
	short channels;
	int sampleRate;
	int byteRate;
	short bitsPerSample;
	short extraParams;
	int dataChunkSize;
	int offset = 0;
	//unsigned char* bufferData;

	if ((fd = open(file, O_RDONLY | O_NOFOLLOW)) == -1)
		return (-1);
	xbuffer[4] = '\0';
	if (read(fd, xbuffer, 4) <= 0 || ft_strncmp(xbuffer, "RIFF", 4) != 0)
		return (error_return("Not a WAV file", NULL));
	offset += 4;

	read(fd, xbuffer, 4);
	offset += 4;

	if (read(fd, xbuffer, 4) <= 0 || ft_strncmp(xbuffer, "WAVE", 4) != 0)
		return (error_return("Not a WAV file", NULL));

	offset += 4;
	if (read(fd, xbuffer, 4) <= 0 || ft_strncmp(xbuffer, "fmt ", 4) != 0)
		return (error_return("Invalid WAV file", NULL));

	offset += 4;
	read(fd, xbuffer, 4);
	offset += 4;
	//short audioFormat = file_read_int16_le(xbuffer, file);
	//short channels = file_read_int16_le(xbuffer, file);
	//int sampleRate = file_read_int32_le(xbuffer, file);
	//int byteRate = file_read_int32_le(xbuffer, file);
	read(fd, &audioFormat, 2);
	offset += 2;
	//endian_swap_short(&audioFormat);
	read(fd, &channels, 2);
	offset += 2;
	//endian_swap_short(&channels);
	read(fd, &sampleRate, 4);
	offset += 4;
	//endian_swap_int(&sampleRate);
	read(fd, &byteRate, 4);
	printf("byterate %d at offset %d\n", byteRate, offset);
	offset += 4;
	//endian_swap_int(&byteRate);

	read(fd, xbuffer, 2);
	offset += 2;
	//short bitsPerSample = file_read_int16_le(xbuffer, file);
	read(fd, &bitsPerSample, 2);
	offset += 2;
	printf("audio format %hd\n", audioFormat);
	printf("buffer %s\n", xbuffer);
	/* if (audioFormat != 16) {
	        //short extraParams = file_read_int16_le(xbuffer, file);
			read(fd, &extraParams, 2);
			offset += 2;
			endian_swap_short(&extraParams);
			printf("extra params = %hd\n", extraParams);
	        //file_ignore_bytes(file, extraParams);
			file_ignore_bytes(fd, extraParams);
			//read(fd, NULL, extraParams);
	}*/extraParams = 0;

	if (read(fd, xbuffer, 4) <= 0 || ft_strncmp(xbuffer, "data", 4) != 0)
		return (error_return("Invalid WAV file", NULL));

	offset += 4;
	//int dataChunkSize = file_read_int32_le(xbuffer, file);
	read(fd, &dataChunkSize, 4);
	printf("reading data chunk size at offset %d\n", offset);
	offset += 4;
	//endian_swap_int(&dataChunkSize);
	printf("datachunk size %d offset %d\n", dataChunkSize, offset);
	//unsigned char* bufferData = file_allocate_and_read_bytes(file, (size_t) dataChunkSize);
	unsigned char *bufferData;
	bufferData = malloc(dataChunkSize);
	read(fd, bufferData, dataChunkSize);
	printf("reading data at offset %d\n", offset);
	printf("data = %s\n", bufferData);

	float duration = (float)dataChunkSize / byteRate;
	printf("duration %f\n", duration);
	alBufferData(buffer, GetFormatFromInfo(channels, bitsPerSample), bufferData, dataChunkSize, sampleRate);
	free(bufferData);
	close(fd);
	return (0);
}