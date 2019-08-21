/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:00:08 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/14 09:38:56 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_oct(int octlen, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	if (flags->precision)
		return (pad_oct_prec(octlen, flags, fd));
	nbpad = flags->field_width - octlen - ((HASH_FLAG) ? 1 : 0);
	padlen = 0;
	padlen += (nbpad > 0 ? nbpad : 0) + ((HASH_FLAG) ? 1 : 0);
	if (nbpad < 0)
		nbpad = 0;
	if ((HASH_FLAG) && (ZERO_FLAG) && !(PREC_FLAG))
		write(fd, "0", 1);
	while (nbpad > 0)
	{
		if ((ZERO_FLAG) && !(PREC_FLAG))
			ft_putchar_fd('0', fd);
		else
			ft_putchar_fd(' ', fd);
		nbpad--;
	}
	if (((HASH_FLAG) && !(ZERO_FLAG)) || (HASH_FLAG && ZERO_FLAG && PREC_FLAG))
		write(fd, "0", 1);
	return (padlen);
}

int	pad_uint_prec(uintmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width - (flags->precision >= ft_unbrlen(number)
			? flags->precision : ft_unbrlen(number));
	if (((PLUS_FLAG) || (SPACE_FLAG)))
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= ft_unbrlen(number) ?
			flags->precision : ft_unbrlen(number)) -
		ft_unbrlen(number);
	padlen = nbpad + nbzero + ((PLUS_FLAG) || (SPACE_FLAG));
	if (!(MIN_FLAG))
		pad_space(nbpad, fd);
	pad_zero(nbzero, fd);
	ft_uitoa_base(number, 10, fd);
	if (MIN_FLAG)
		pad_space(nbpad, fd);
	return (padlen);
}

int	pad_uint(uintmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_unbrlen(number);
	nbpad = (nbpad < 0 ? 0 : nbpad);
	padlen = nbpad;
	if ((ZERO_FLAG) && !(MIN_FLAG))
	{
		if ((SPACE_FLAG) && !(PLUS_FLAG))
		{
			ft_putchar_fd(' ', fd);
			nbpad--;
		}
		while (nbpad > 0)
		{
			ft_putchar_fd('0', fd);
			nbpad--;
		}
	}
	while (nbpad > 0)
	{
		ft_putchar_fd(' ', fd);
		nbpad--;
	}
	return (padlen);
}

int	pad_int_prec(intmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;
	int nbrlen;

	nbrlen = ft_nbrlen(number) - (number < 0 ? 1 : 0);
	nbpad = flags->field_width -
		(flags->precision >= nbrlen ? flags->precision : nbrlen) -
		(number < 0 ? 1 : 0) -
		(((PLUS_FLAG) || (SPACE_FLAG)) && number >= 0 ? 1 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= nbrlen ? flags->precision : nbrlen) - nbrlen;
	padlen = 0;
	flags_spec(flags, nbpad, fd, number);
	if (number < 0)
		ft_putchar_fd('-', fd);
	pad_zero(nbzero, fd);
	ft_putnbr_fd(ft_absolute(number), fd);
	if (MIN_FLAG)
	{
		pad_space(nbpad, fd);
	}
	padlen = nbpad + nbzero + (number >= 0 ? (PLUS_FLAG) || (SPACE_FLAG) : 0);
	return (padlen);
}

int	pad_str(int number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - number;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad;
	if ((ZERO_FLAG) && !(MIN_FLAG))
	{
		pad_zero(nbpad, fd);
		return (padlen);
	}
	pad_space(nbpad, fd);
	return (padlen);
}
