/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:44:18 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 18:50:07 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_bin_prec_min(int binlen, t_flags *flags, int fd, uintmax_t bin)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width - (flags->precision >= binlen ? flags->precision
		: binlen) - (flags->precision <= binlen ? (HASH_FLAG) : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= binlen ? flags->precision : binlen) - binlen;
	padlen = nbpad + nbzero + ((HASH_FLAG)
			&& flags->precision <= binlen ? 1 : 0);
	if ((HASH_FLAG) && flags->precision <= binlen)
		write(fd, "0", 1);
	pad_zero(nbzero, fd);
	ft_uitoa_base(bin, 2, fd);
	if (flags->precision < flags->field_width)
		pad_space(nbpad, fd);
	return (padlen);
}

int	pad_bin_prec(int binlen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width - (flags->precision >= binlen ? flags->precision
		: binlen) - (flags->precision <= binlen ? (HASH_FLAG) : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= binlen ? flags->precision : binlen) - binlen;
	padlen = nbpad + nbzero + ((HASH_FLAG)
			&& flags->precision <= binlen ? 1 : 0);
	if (flags->precision < flags->field_width)
	{
		pad_space(nbpad, fd);
		if ((HASH_FLAG) && flags->precision <= binlen)
			write(fd, "0", 1);
		pad_zero(nbzero, fd);
	}
	else
	{
		if ((HASH_FLAG) && flags->precision <= binlen)
			write(fd, "0", 1);
		pad_zero(nbzero, fd);
	}
	return (padlen);
}

int	pad_bin(int binlen, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	if (flags->precision)
		return (pad_bin_prec(binlen, flags, fd));
	nbpad = flags->field_width - binlen - ((HASH_FLAG) ? 1 : 0);
	padlen = 0;
	padlen += (nbpad > 0 ? nbpad : 0) + ((HASH_FLAG) ? 1 : 0);
	if (nbpad < 0)
		nbpad = 0;
	if ((HASH_FLAG) && (ZERO_FLAG))
		write(fd, "0", 1);
	while (nbpad > 0)
	{
		if ((ZERO_FLAG))
			ft_putchar_fd('0', fd);
		else
			ft_putchar_fd(' ', fd);
		nbpad--;
	}
	if ((HASH_FLAG) && !(ZERO_FLAG))
		write(fd, "0", 1);
	return (padlen);
}

int	special_convert_bin(uintmax_t bin, int fd, t_flags *flags)
{
	int full_len;
	int binlen;

	full_len = 0;
	binlen = ft_uintlen_base(bin, 2);
	if (MIN_FLAG)
	{
		full_len += pad_bin_prec_min(binlen, flags, fd, bin);
		return (full_len + binlen);
	}
	full_len += pad_bin(binlen, flags, fd);
	ft_uitoa_base(bin, 2, fd);
	return (full_len + binlen);
}

int	convert_bin(va_list args, int fd, t_flags *flags)
{
	uintmax_t	bin;
	int			binlen;

	if (HH_FLAG)
		bin = (unsigned char)va_arg(args, unsigned int);
	else if (H_FLAG)
		bin = (unsigned short)va_arg(args, unsigned int);
	else if (L_FLAG)
		bin = (unsigned long)va_arg(args, unsigned long);
	else if (LL_FLAG)
		bin = (unsigned long long)va_arg(args, unsigned long long);
	else
		bin = va_arg(args, unsigned int);
	if (is_activated(flags))
		return (special_convert_bin(bin, fd, flags));
	binlen = ft_uitoa_base(bin, 2, fd);
	return (binlen);
}
