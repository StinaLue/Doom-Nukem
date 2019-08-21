/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 11:04:22 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/05 09:54:02 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_hex_prec_min(int hexlen, t_flags *flags, int fd, uintmax_t hex)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width -
		(flags->precision >= hexlen ? flags->precision : hexlen) -
		((HASH_FLAG) ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
	padlen = nbpad + nbzero + ((HASH_FLAG) ? 2 : 0)
		+ (flags->precision < hexlen ? 0 : 0);
	if ((HASH_FLAG))
		write(fd, "0x", 2);
	pad_zero(nbzero, fd);
	ft_uitoa_base(hex, 16, fd);
	if (flags->precision < flags->field_width)
		pad_space(nbpad, fd);
	return (padlen);
}

int	pad_hex_prec(int hexlen, t_flags *flags, int fd, char letter)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width -
		(flags->precision >= hexlen ? flags->precision : hexlen) -
		((HASH_FLAG) ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
	padlen = nbpad + nbzero + ((HASH_FLAG) ? 2 : 0)
		+ (flags->precision < hexlen ? 0 : 0);
	if (flags->precision < flags->field_width)
		pad_space(nbpad, fd);
	if ((HASH_FLAG))
		letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
	pad_zero(nbzero, fd);
	return (padlen);
}

int	pad_hex(int hexlen, t_flags *flags, int fd, char letter)
{
	int nbpad;
	int padlen;

	if (flags->precision || PREC_FLAG)
		return (pad_hex_prec(hexlen, flags, fd, letter));
	nbpad = flags->field_width - hexlen - ((HASH_FLAG) ? 2 : 0);
	padlen = 0;
	padlen += (nbpad > 0 ? nbpad : 0) + ((HASH_FLAG) ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	if ((HASH_FLAG) && (ZERO_FLAG))
		letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
	while (nbpad > 0)
	{
		if ((ZERO_FLAG))
			ft_putchar_fd('0', fd);
		else
			ft_putchar_fd(' ', fd);
		nbpad--;
	}
	if ((HASH_FLAG) && !(ZERO_FLAG))
		letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
	return (padlen);
}

int	special_convert_hex(uintmax_t hex, int fd, t_flags *flags, char letter)
{
	int full_len;
	int hexlen;

	full_len = 0;
	hexlen = ft_uintlen_base(hex, 16);
	if (((HASH_FLAG) || (PREC_FLAG)) && hex == 0)
		return (special_hexzero(fd, flags));
	if (MIN_FLAG)
	{
		if (letter == 'x')
			full_len += pad_hex_prec_min(hexlen, flags, fd, hex);
		else if (letter == 'X')
			full_len += pad_hex_prec_mincap(hexlen, flags, fd, hex);
		return (full_len + hexlen);
	}
	full_len += pad_hex(hexlen, flags, fd, letter);
	if (letter == 'x')
		ft_uitoa_base(hex, 16, fd);
	else if (letter == 'X')
		ft_uitocapa_base(hex, 16, fd);
	return (full_len + hexlen);
}

int	convert_hex(va_list args, int fd, t_flags *flags)
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
		return (special_convert_hex(hex, fd, flags, 'x'));
	hexlen = ft_uitoa_base(hex, 16, fd);
	return (hexlen);
}
