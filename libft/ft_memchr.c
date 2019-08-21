/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:43:14 by afonck            #+#    #+#             */
/*   Updated: 2018/11/12 09:41:46 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s1;

	i = 0;
	s1 = s;
	while (i < n && n != 0)
	{
		if (*s1 == (unsigned char)c)
			return ((void *)s1);
		s1++;
		i++;
	}
	return (NULL);
}
