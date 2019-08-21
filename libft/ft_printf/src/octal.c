/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:00:21 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/06 14:45:37 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_oct_prec_min(int octlen, t_flags *flags, int fd, uintmax_t oct)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width -
		(flags->precision >= octlen ? flags->precision : octlen) -
		(flags->precision <= octlen ? (HASH_FLAG) : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= octlen ? flags->precision : octlen) - octlen;
	padlen = nbpad + nbzero +
		((HASH_FLAG) && flags->precision <= octlen ? 1 : 0);
	if ((HASH_FLAG) && flags->precision <= octlen)
		write(fd, "0", 1);
	pad_zero(nbzero, fd);
	ft_uitoa_base(oct, 8, fd);
	if (flags->precision < flags->field_width)
		pad_space(nbpad, fd);
	return (padlen);
}

int	pad_oct_prec(int octlen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width -
		(flags->precision >= octlen ? flags->precision : octlen) -
		(flags->precision <= octlen ? (HASH_FLAG) : 0);
	nbpad = (nbpad < 0 ? 0 : nbpad);
	nbzero = (flags->precision >= octlen ? flags->precision : octlen) - octlen;
	padlen = nbpad + nbzero +
		((HASH_FLAG) && flags->precision <= octlen ? 1 : 0);
	if (flags->precision < flags->field_width)
	{
		pad_space(nbpad, fd);
		if ((HASH_FLAG) && flags->precision <= octlen)
			write(fd, "0", 1);
		pad_zero(nbzero, fd);
	}
	else
	{
		if ((HASH_FLAG) && flags->precision <= octlen)
			write(fd, "0", 1);
		pad_zero(nbzero, fd);
	}
	return (padlen);
}

int	special_octzero(int fd, t_flags *flags)
{
	int len;

	len = flags->field_width + ((HASH_FLAG) && !flags->field_width ? 1 : 0);
	if (HASH_FLAG)
	{
		if (PREC_FLAG && !(MIN_FLAG))
			pad_space(len - 1, fd);
		if (!(PREC_FLAG) && !(MIN_FLAG))
			pad_zero(len - 1, fd);
		write(1, "0", 1);
		if (MIN_FLAG)
			pad_space(len - 1, fd);
		return (len);
	}
	pad_space(len, fd);
	return (len);
}

int	special_convert_oct(uintmax_t oct, int fd, t_flags *flags)
{
	int full_len;
	int octlen;

	full_len = 0;
	octlen = ft_uintlen_base(oct, 8);
	if (oct == 0 && (PREC_FLAG || HASH_FLAG) && flags->precision == 0)
		return (special_octzero(fd, flags));
	if (MIN_FLAG)
	{
		full_len += pad_oct_prec_min(octlen, flags, fd, oct);
		return (full_len + octlen);
	}
	full_len += pad_oct(octlen, flags, fd);
	ft_uitoa_base(oct, 8, fd);
	return (full_len + octlen);
}

int	convert_oct(va_list args, int fd, t_flags *flags)
{
	uintmax_t	oct;
	int			octlen;

	if (HH_FLAG)
		oct = (unsigned char)va_arg(args, unsigned int);
	else if (H_FLAG)
		oct = (unsigned short)va_arg(args, unsigned int);
	else if (L_FLAG)
		oct = (unsigned long)va_arg(args, unsigned long);
	else if (LL_FLAG)
		oct = (unsigned long long)va_arg(args, unsigned long long);
	else
		oct = va_arg(args, unsigned int);
	if (is_activated(flags) || PREC_FLAG)
		return (special_convert_oct(oct, fd, flags));
	octlen = ft_uitoa_base(oct, 8, fd);
	return (octlen);
}
