/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 08:51:23 by afonck            #+#    #+#             */
/*   Updated: 2018/11/15 09:23:41 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;

	temp = 0;
	while (*alst)
	{
		temp = (*alst)->next;
		ft_lstdelone(alst, del);
		(*alst) = temp;
	}
	ft_lstdelone(&temp, del);
}
