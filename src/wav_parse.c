/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wav_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 00:15:56 by afonck            #+#    #+#             */
/*   Updated: 2020/02/12 11:03:07 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "al.h"
#include "libft.h"
#include "libwav.h"

ALenum		get_format_from_info(short channels, short bits_per_sample)
{
	bits_per_sample = 0;
	if (channels == 1)
		return (AL_FORMAT_MONO16);
	return (AL_FORMAT_STEREO16);
}

int			read_riff_chunk(int fd, char *xbuffer, char *file, int *offset)
{
	if (read(fd, xbuffer, 4) != 4 || ft_strncmp(xbuffer, "RIFF", 4) != 0)
		return (error_return_wav("Not a WAV file\n", NULL, fd));
	*offset += 4;
	if ((read(fd, xbuffer, 4)) != 4)
		return (error_return_wav("Unexpected EOF in %{r}s\n", file, fd));
	*offset += 4;
	if (read(fd, xbuffer, 4) != 4 || ft_strncmp(xbuffer, "WAVE", 4) != 0)
		return (error_return_wav("Not a WAV file\n", NULL, fd));
	*offset += 4;
	return (0);
}

int			read_fmt_chunk(t_wav *wav, int fd, char *xbuffer, int *offset)
{
	if (read(fd, xbuffer, 4) != 4 || ft_strncmp(xbuffer, "fmt ", 4) != 0)
		return (error_return_wav("Invalid WAV file\n", NULL, fd));
	*offset += 4;
	if ((read(fd, xbuffer, 4)) != 4)
		return (error_return_wav("Unexpected EOF\n", NULL, fd));
	*offset += 4;
	read(fd, &wav->audio_format, 2);
	*offset += 2;
	read(fd, &wav->channels, 2);
	*offset += 2;
	read(fd, &wav->sample_rate, 4);
	*offset += 4;
	read(fd, &wav->byte_rate, 4);
	*offset += 4;
	if ((read(fd, xbuffer, 2)) != 2)
		return (error_return_wav("Unexpected EOF\n", NULL, fd));
	*offset += 2;
	read(fd, &wav->bits_per_sample, 2);
	*offset += 2;
	return (0);
}

int			read_data_chunk(t_wav *wav, int fd, char *xbuffer, int *offset)
{
	if (read(fd, xbuffer, 4) <= 0 || ft_strncmp(xbuffer, "data", 4) != 0)
		return (error_return_wav("Invalid WAV file\n", NULL, fd));
	*offset += 4;
	read(fd, &wav->data_chunk_size, 4);
	*offset += 4;
	if ((wav->buffer_data = malloc(wav->data_chunk_size)) == NULL)
		return (error_return_wav("Malloc error for wav data size\n", NULL, fd));
	if (read(fd, wav->buffer_data, \
			wav->data_chunk_size) != wav->data_chunk_size)
	{
		ft_memdel((void **)&wav->buffer_data);
		return (error_return_wav("Error while reading wav data\n", NULL, fd));
	}
	wav->duration = (float)wav->data_chunk_size / wav->byte_rate;
	return (0);
}

int			load_wav(char *file, ALuint buffer)
{
	int		fd;
	char	xbuffer[5];
	t_wav	wav;
	int		offset;

	wav.buffer_data = NULL;
	offset = 0;
	if (!file || (is_wav(file) != 1))
		return (1);
	if ((fd = open(file, O_RDONLY | O_NOFOLLOW)) == -1)
		return (error_return_wav("failed to open %{r}s\n", file, fd));
	xbuffer[4] = '\0';
	if (read_riff_chunk(fd, xbuffer, file, &offset) != 0)
		return (1);
	if (read_fmt_chunk(&wav, fd, xbuffer, &offset) != 0)
		return (1);
	if (read_data_chunk(&wav, fd, xbuffer, &offset) != 0)
		return (1);
	alBufferData(buffer, get_format_from_info(wav.channels, \
				wav.bits_per_sample), wav.buffer_data, wav.data_chunk_size, \
				wav.sample_rate);
	ft_memdel((void **)&wav.buffer_data);
	close(fd);
	return (0);
}
