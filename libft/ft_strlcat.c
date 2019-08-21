/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:25:04 by afonck            #+#    #+#             */
/*   Updated: 2018/11/11 17:46:47 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static size_t	dstlen(char *dst)
{
	size_t i;

	i = 0;
	while (dst[i] != '\0')
		i++;
	return (i);
}

static size_t	srclen(const char *src)
{
	size_t i;

	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	initial;

	i = 0;
	j = 0;
	initial = dstlen(dst);
	if (size <= initial)
		return (size + srclen(src));
	while (dst[i] != '\0')
		i++;
	while (j < (size - initial - 1) && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (initial + srclen(src));
}
