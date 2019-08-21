/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexcap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 09:50:42 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/05 10:08:49 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_hex_prec_mincap(int hexlen, t_flags *flags, int fd, uintmax_t hex)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width -
		(flags->precision >= hexlen ? flags->precision : hexlen) -
		((HASH_FLAG) ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= hexlen ? flags->precision : hexlen)
		- hexlen;
	padlen = nbpad + nbzero + ((HASH_FLAG) ? 2 : 0)
		+ (flags->precision < hexlen ? 0 : 0);
	if ((HASH_FLAG))
		write(fd, "0X", 2);
	pad_zero(nbzero, fd);
	ft_uitocapa_base(hex, 16, fd);
	if (flags->precision < flags->field_width)
		pad_space(nbpad, fd);
	return (padlen);
}

int	special_hexzero(int fd, t_flags *flags)
{
	int spacelen;
	int fullen;

	spacelen = flags->field_width - flags->precision - (PREC_FLAG ? 0 : 1);
	spacelen = spacelen < 0 ? 0 : spacelen;
	fullen = (flags->field_width <= flags->precision ? flags->precision
			: spacelen + flags->precision) + (PREC_FLAG ? 0 : 1);
	if (MIN_FLAG)
	{
		if (HASH_FLAG && !(PREC_FLAG))
			ft_putchar_fd('0', fd);
		pad_zero(flags->precision, fd);
		pad_space(spacelen, fd);
	}
	else
	{
		if (ZERO_FLAG && !(PREC_FLAG))
			pad_zero(spacelen, fd);
		else
			pad_space(spacelen, fd);
		pad_zero(flags->precision, fd);
		if (HASH_FLAG && !(PREC_FLAG))
			ft_putchar_fd('0', fd);
	}
	return (fullen);
}

int	convert_cap_hex(va_list args, int fd, t_flags *flags)
{
	uintmax_t	hex;
	int			hexlen;

	if (HH_FLAG)
		hex = (unsigned char)va_arg(args, unsigned int);
	else if (H_FLAG)
		hex = (unsigned short)va_arg(args, unsigned int);
	else if (L_FLAG)
		hex = (unsigned long)va_arg(args, unsigned long);
	else if (LL_FLAG)
		hex = (unsigned long long)va_arg(args, unsigned long long);
	else
		hex = va_arg(args, unsigned int);
	if (is_activated(flags) || PREC_FLAG)
		return (special_convert_hex(hex, fd, flags, 'X'));
	hexlen = ft_uitocapa_base(hex, 16, fd);
	return (hexlen);
}
