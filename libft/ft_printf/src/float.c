/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:10:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/06 15:03:41 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		float_precision(double number, int preclen, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(MIN_FLAG))
	{
		if (!(1 / number > 0) && (ZERO_FLAG) && number != 0)
			ft_putchar_fd('-', fd);
		len += pad_float_prec(number, preclen, flags, fd);
	}
	else
	{
		if (!(1 / number > 0) && (ZERO_FLAG) && number != 0)
			ft_putchar_fd('-', fd);
		len += pad_float_prec(number, preclen, flags, fd);
	}
	return (len);
}

int		float_no_precision(double number, int preclen, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(MIN_FLAG))
	{
		if ((PLUS_FLAG) && (ZERO_FLAG) && (1 / number > 0))
			ft_putchar_fd('+', fd);
		if (!(1 / number > 0) && number == 0)
			ft_putchar_fd('-', fd);
		len += pad_float(number, flags, fd);
		if (!(1 / number > 0) && number != 0)
			ft_putchar_fd('-', fd);
		if ((PLUS_FLAG) && !(ZERO_FLAG) && (1 / number > 0))
			ft_putchar_fd('+', fd);
		ft_ftoa_fd(ft_absfloat(number), preclen, fd);
		return (len);
	}
	if ((PLUS_FLAG) && (1 / number > 0))
		ft_putchar_fd('+', fd);
	else if ((SPACE_FLAG) && (1 / number > 0))
		ft_putchar_fd(' ', fd);
	if (!(1 / number > 0) && number == 0)
		ft_putchar_fd('-', fd);
	ft_ftoa_fd(number, preclen, fd);
	return (len += pad_float(number, flags, fd));
}

int		pad_float(double number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_floatlen(number, 6);
	if (((PLUS_FLAG) || (SPACE_FLAG)) && (1 / number > 0))
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + ((1 / number > 0) ? (PLUS_FLAG) || (SPACE_FLAG) : 0);
	if ((ZERO_FLAG) && !(MIN_FLAG))
	{
		if ((SPACE_FLAG) && !(PLUS_FLAG) && number < 0)
			ft_putchar_fd(' ', fd);
		pad_zero(nbpad, fd);
		return (padlen);
	}
	if ((SPACE_FLAG) && !(PLUS_FLAG) && (1 / number > 0))
		ft_putchar_fd(' ', fd);
	pad_space(nbpad, fd);
	return (padlen);
}

int		special_convert_float(double number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision)
	{
		full_len += float_precision(number, flags->precision, fd, flags);
		return (full_len + ft_floatlen(number, flags->precision));
	}
	else if (!flags->precision && (PREC_FLAG))
	{
		full_len += float_precision(number, 0, fd, flags);
		return (full_len + ft_floatlen(number, 0));
	}
	else
	{
		full_len += float_no_precision(number, 6, fd, flags);
		return (full_len + ft_floatlen(number, 6));
	}
}

int		convert_float(va_list args, int fd, t_flags *flags)
{
	long double	numberldb;
	double		numberdb;
	int			nblen;

	nblen = 0;
	numberldb = 0;
	numberdb = 0;
	if (BIGL_FLAG)
		numberldb = va_arg(args, long double);
	else
		numberdb = va_arg(args, double);
	if (BIGL_FLAG)
	{
		if (is_activated(flags) || (PREC_FLAG) ||
				(!(1 / numberldb > 0) && numberldb == 0))
			return (special_convert_float(numberldb, fd, flags));
		nblen += ft_ftoa_fd(numberldb, 6, fd);
		return (nblen);
	}
	if (is_activated(flags) || (PREC_FLAG) ||
			(!(1 / numberdb > 0) && numberdb == 0))
		return (special_convert_float(numberdb, fd, flags));
	nblen += ft_ftoa_fd(numberdb, 6, fd);
	return (nblen);
}
