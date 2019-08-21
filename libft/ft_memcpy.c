/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:16:34 by afonck            #+#    #+#             */
/*   Updated: 2018/11/11 18:05:23 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
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
