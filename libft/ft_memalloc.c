/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:51:51 by afonck            #+#    #+#             */
/*   Updated: 2018/11/12 10:43:05 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static void		setmemo(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			i;

	p = b;
	i = 0;
	while (i < len)
	{
		*p = (unsigned char)c;
		p++;
		i++;
	}
}

static void		zero(void *s, size_t n)
{
	if (n != 0)
		setmemo(s, '\0', n);
}

void			*ft_memalloc(size_t size)
{
	void	*ptr;

	if ((ptr = (void *)malloc(sizeof(size_t) * size)) == NULL)
		return (NULL);
	zero(ptr, size);
	return (ptr);
}
