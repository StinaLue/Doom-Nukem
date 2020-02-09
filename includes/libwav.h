/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libwav.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:43:21 by afonck            #+#    #+#             */
/*   Updated: 2020/02/08 20:12:03 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBWAV_H
# define LIBWAV_H

typedef struct		s_wav
{
	unsigned char	*buffer_data;
	float			duration;
	int				sample_rate;
	int				byte_rate;
	int				data_chunk_size;
	short			bits_per_sample;
	short			extra_params;
	short			audio_format;
	short			channels;
}					t_wav;

int					error_return_wav(char *s1, char *s2, int fd);
#endif
