/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wav_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 00:15:56 by afonck            #+#    #+#             */
/*   Updated: 2020/02/05 20:15:51 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "al.h"
#include "libft.h"
#include "libwav.h"

static int error_return(char *s1, char *s2, int fd)
{
	if (fd != -1)
	{
		if (close(fd) != 0)
			ft_dprintf(STDERR_FILENO, "error while closing file\n");
	}
    if (s1 && s2)
        ft_dprintf(STDERR_FILENO, s1, s2);
    else
        ft_dprintf(STDERR_FILENO, s1);
    return (1);
}

ALenum GetFormatFromInfo(short channels, short bits_per_sample)
{
	bits_per_sample = 0;
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

void file_ignore_bytes(int fd, short extra_params)
{
	char buf[1];

	while (extra_params > 0)
	{
		read(fd, buf, 1);
		extra_params--;
	}
}

static int	is_wav(char *file)
{
	int	len;

	len = 0;
	while (file[len])
		len++;
	len -= 1;
	if (len < 4)
		return (0);
	if (file[len--] != 'v')
		return (0);
	if (file[len--] != 'a')
		return (0);
	if (file[len--] != 'w')
		return (0);
	if (file[len] != '.')
		return (0);
	return (1);
}

int	read_RIFF_chunk(int fd, char *xbuffer, char *file, int *offset)
{
	if (read(fd, xbuffer, 4) != 4 || ft_strncmp(xbuffer, "RIFF", 4) != 0)
	return (error_return("Not a WAV file\n", NULL, fd));
	*offset += 4;

	if ((read(fd, xbuffer, 4)) != 4)
		return (error_return("Unexpected EOF in %{r}s\n", file, fd));
	*offset += 4;

	if (read(fd, xbuffer, 4) != 4 || ft_strncmp(xbuffer, "WAVE", 4) != 0)
		return (error_return("Not a WAV file\n", NULL, fd));

	*offset += 4;
	return (0);
}

int	read_fmt_chunk(t_wav *wav, int fd, char *xbuffer, int *offset)
{
	if (read(fd, xbuffer, 4) != 4 || ft_strncmp(xbuffer, "fmt ", 4) != 0)
		return (error_return("Invalid WAV file\n", NULL, fd));
	*offset += 4;
	if ((read(fd, xbuffer, 4)) != 4)
		return (error_return("Unexpected EOF\n", NULL, fd));
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
		return (error_return("Unexpected EOF\n", NULL, fd));
	*offset += 2;
	read(fd, &wav->bits_per_sample, 2);
	*offset += 2;
	return (0);
}

int	read_data_chunk(t_wav *wav, int fd, char *xbuffer, int *offset)
{
	if (read(fd, xbuffer, 4) <= 0 || ft_strncmp(xbuffer, "data", 4) != 0)
		return (error_return("Invalid WAV file\n", NULL, fd));
	*offset += 4;
	read(fd, &wav->data_chunk_size, 4);
	*offset += 4;
	if ((wav->buffer_data = malloc(wav->data_chunk_size)) == NULL)
		return (error_return("Malloc error for wav data size\n", NULL, fd));
	if (read(fd, wav->buffer_data, wav->data_chunk_size) != wav->data_chunk_size)
	{
		ft_memdel((void **)&wav->buffer_data);
		return (error_return("Error while reading wav data\n", NULL, fd));
	}
	wav->duration = (float)wav->data_chunk_size / wav->byte_rate;
	return (0);
}

int	load_wav(char *file, ALuint buffer)
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
		return (error_return("failed to open %{r}s\n", file, fd));
	xbuffer[4] = '\0';
	
	if (read_RIFF_chunk(fd, xbuffer, file, &offset) != 0)
		return (1);
	if (read_fmt_chunk(&wav, fd, xbuffer, &offset) != 0)
		return (1);
	if (read_data_chunk(&wav, fd, xbuffer, &offset) != 0)
		return (1);
	/* if (audio_format != 16) {
	        //short extra_params = file_read_int16_le(xbuffer, file);
			read(fd, &extra_params, 2);
			offset += 2;
			endian_swap_short(&extra_params);
			printf("extra params = %hd\n", extra_params);
	        //file_ignore_bytes(file, extra_params);
			file_ignore_bytes(fd, extra_params);
			//read(fd, NULL, extra_params);
	}*///extra_params = 0;
	alBufferData(buffer, GetFormatFromInfo(wav.channels, wav.bits_per_sample), wav.buffer_data, wav.data_chunk_size, wav.sample_rate);
	ft_memdel((void **)&wav.buffer_data);
	close(fd);
	return (0);
}