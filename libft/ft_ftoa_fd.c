/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:46:26 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 18:03:41 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_decimal(double n, double fpart, int afterpoint, int fd)
{
	int morezero;

	morezero = 0;
	if (afterpoint != 0)
	{
		ft_putchar_fd('.', fd);
		fpart = fpart * ft_pow(10, afterpoint);
		fpart = (n >= 0 ? fpart + 0.5 : fpart - 0.5);
		fpart = ft_absolute(fpart);
		morezero = afterpoint - ft_nbrlen((long)fpart);
		if (morezero > 0)
			pad_zero(morezero, fd);
		ft_uitoa_base((unsigned long)fpart, 10, fd);
	}
}

int			ft_ftoa_fd(double n, int afterpoint, int fd)
{
	int		len;
	long	ipart;
	double	fpart;

	len = afterpoint + (afterpoint > 0 ? 1 : 0);
	ipart = (long)n;
	fpart = n - (double)ipart;
	if (ipart == 0 && !(1 / n > 0) && n != 0)
	{
		len++;
		write(fd, "-", 1);
	}
	len += ft_nbrlen(ipart);
	if (afterpoint == 0)
	{
		if (fpart > 0.5)
			ipart += 1;
		else if (fpart < -0.5)
			ipart -= 1;
	}
	ft_putnbr_fd(ipart, fd);
	handle_decimal(n, fpart, afterpoint, fd);
	return (len);
}
