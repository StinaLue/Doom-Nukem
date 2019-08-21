/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 09:17:49 by afonck            #+#    #+#             */
/*   Updated: 2019/07/05 09:18:42 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putwchar_fd(wchar_t wchar, int fd)
{
	unsigned int	ch;
	int				n;

	ch = (unsigned int)wchar;
	n = ft_nbits(ch);
	if (n > 7)
	{
		if (n > 11)
		{
			if (n > 16)
			{
				ft_putchar_fd(((ch >> 18) & 7) | 240, fd);
				ft_putchar_fd(((ch >> 12) & 63) | 128, fd);
			}
			else
				ft_putchar_fd(((ch >> 12) & 15) | 224, fd);
			ft_putchar_fd(((ch >> 6) & 63) | 128, fd);
		}
		else
			ft_putchar_fd(((ch >> 6) & 31) | 192, fd);
		ft_putchar_fd((ch & 63) | 128, fd);
	}
	else
		ft_putchar_fd(ch, fd);
	return (ft_wcharlen(n));
}
