/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:12:05 by afonck            #+#    #+#             */
/*   Updated: 2018/11/14 10:49:37 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void		*cpymem(void *dst, const void *src, size_t n)
{
	char	*dst1;
	char	*src1;
	size_t	i;

	i = 0;
	dst1 = (char *)dst;
	src1 = (char *)src;
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return ((void *)dst1);
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst1;
	const char	*src1;
	size_t		i;

	dst1 = (char *)dst;
	src1 = (const char *)src;
	i = len;
	if (dst < src)
		return (cpymem(dst, src, len));
	else
	{
		while (i > 0)
		{
			dst1[i - 1] = src1[i - 1];
			i--;
		}
	}
	return (dst);
}
