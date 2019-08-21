/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:50:16 by afonck            #+#    #+#             */
/*   Updated: 2018/11/15 09:24:07 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	*cpymem(void *dst, const void *src, size_t n)
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

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if ((new = (t_list *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if ((new->content = (void *)malloc(content_size)) == NULL)
		{
			free(new);
			return (NULL);
		}
		cpymem(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
