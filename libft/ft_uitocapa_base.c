/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitocapa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:34:46 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/27 18:00:43 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uitocapa_base(uintmax_t value, int base, int fd)
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
			ascii_offset = 7;
		*--ptr = '0' + ((value % base) + ascii_offset);
		value /= base;
	}
	write(fd, ptr, ft_strlen(ptr));
	return (ft_strlen(ptr));
}
