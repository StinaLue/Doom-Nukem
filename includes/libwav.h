/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libwav.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:43:21 by afonck            #+#    #+#             */
/*   Updated: 2020/01/31 15:36:37 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct		s_wav
{
	unsigned char	*bufferData;
	float			duration;
	int				sampleRate;
	int				byteRate;
	int				dataChunkSize;
	short			bitsPerSample;
	short			extraParams;
	short			audioFormat;
	short			channels;
}					t_wav;
