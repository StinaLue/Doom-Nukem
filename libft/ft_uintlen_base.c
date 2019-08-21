/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintlen_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:08:43 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 15:11:22 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_uintlen_base(uintmax_t value, int base)
{
	char	buf[50];
	char	*ptr;
	int		num;
	int		ascii_offset;

	ptr = &buf[49];
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
