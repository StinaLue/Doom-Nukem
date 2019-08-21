/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintptrtoalen_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:37:01 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 15:34:20 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uintptrtoalen_base(uintptr_t value, int base)
{
	char	buf[(sizeof(uintptr_t) * 2) + 1];
	char	*ptr;
	int		num;
	int		ascii_offset;

	ptr = &buf[(sizeof(uintptr_t) * 2)];
	*ptr = '\0';
	num = value;
	if (value == 0)
		*--ptr = '0' + (value % base);
	while (value != 0)
	{
		ascii_offset = 0;
		if (value % base > 9)
			ascii_offset = 39;
		*--ptr = '0' + ((value % base) + ascii_offset);
		value /= base;
	}
	return (ft_strlen(ptr));
}
