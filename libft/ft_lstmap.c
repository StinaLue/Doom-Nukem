/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:28:28 by afonck            #+#    #+#             */
/*   Updated: 2018/11/15 13:32:25 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void				*cpymem(void *dst, const void *src, size_t n)
{
	char		*dst1;
	const char	*src1;
	size_t		i;

	i = 0;
	dst1 = (char *)dst;
	src1 = (const char *)src;
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst);
}

static t_list			*newlst(void const *content, size_t content_size)
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

t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newelem;
	t_list *begin;
	t_list *temp;

	if (lst == NULL || f == NULL)
		return (NULL);
	temp = (*f)(lst);
	if ((newelem = newlst(temp->content, temp->content_size)) == NULL)
		return (NULL);
	begin = newelem;
	lst = lst->next;
	while (lst)
	{
		temp = (*f)(lst);
		if ((newelem->next = newlst(temp->content, temp->content_size)) == NULL)
		{
			free(begin);
			return (NULL);
		}
		lst = lst->next;
		newelem = newelem->next;
	}
	return (begin);
}
