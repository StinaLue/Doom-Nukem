/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:06:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/06 14:45:55 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	int_no_precision(intmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(MIN_FLAG))
	{
		if ((PLUS_FLAG) && (ZERO_FLAG) && number >= 0)
			ft_putchar_fd('+', fd);
		if (number < 0 && (ZERO_FLAG))
			ft_putchar_fd('-', fd);
		len += pad_int(number, flags, fd);
		if ((PLUS_FLAG) && !(ZERO_FLAG) && number >= 0)
			ft_putchar_fd('+', fd);
		ft_putnbr_fd(ft_absolute(number), fd);
		return (len);
	}
	if ((PLUS_FLAG) && number >= 0)
		ft_putchar_fd('+', fd);
	else if ((SPACE_FLAG) && number >= 0)
		ft_putchar_fd(' ', fd);
	else if (number == -9223372036854775807 - 1)
		ft_putchar_fd('-', fd);
	ft_putnbr_fd(number, fd);
	len += pad_int(number, flags, fd);
	return (len);
}

int	pad_int(intmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_nbrlen(number);
	if (((PLUS_FLAG) || (SPACE_FLAG)) && number >= 0)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (number >= 0 ? (PLUS_FLAG) || (SPACE_FLAG) : 0);
	if ((ZERO_FLAG) && !(MIN_FLAG) && !((PREC_FLAG) && (flags->precision == 0)))
	{
		if ((SPACE_FLAG) && !(PLUS_FLAG) && number >= 0)
			ft_putchar_fd(' ', fd);
		pad_zero(nbpad, fd);
		return (padlen);
	}
	if ((SPACE_FLAG) && !(PLUS_FLAG) && !(MIN_FLAG) && number >= 0)
		ft_putchar_fd(' ', fd);
	pad_space(nbpad, fd);
	if (number < 0 && !(MIN_FLAG))
		ft_putchar_fd('-', fd);
	return (padlen);
}

int	special_zero(int fd, t_flags *flags)
{
	int len;

	len = flags->field_width - (PLUS_FLAG || SPACE_FLAG ? 1 : 0);
	if (len < 0)
		len = 0;
	if (((PLUS_FLAG) || (SPACE_FLAG)) && (MIN_FLAG))
	{
		if (PLUS_FLAG)
			ft_putchar_fd('+', fd);
		else if (SPACE_FLAG)
			ft_putchar_fd(' ', fd);
	}
	pad_space(len, fd);
	if (((PLUS_FLAG) || (SPACE_FLAG)) && !(MIN_FLAG))
	{
		if (PLUS_FLAG)
			ft_putchar_fd('+', fd);
		else if (SPACE_FLAG)
			ft_putchar_fd(' ', fd);
		len++;
	}
	if (((PLUS_FLAG) || (SPACE_FLAG)) && (MIN_FLAG))
		len++;
	return (len);
}

int	special_convert_int(intmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (((PREC_FLAG) && flags->precision == 0) && number == 0)
		return (special_zero(fd, flags));
	else if (flags->precision || (PREC_FLAG))
	{
		if (!(MIN_FLAG))
			len += pad_int_prec(number, flags, fd);
		else
			len += pad_int_prec(number, flags, fd);
	}
	else
		len += int_no_precision(number, fd, flags);
	return (len + ft_nbrlen(number));
}

int	convert_int(va_list args, int fd, t_flags *flags)
{
	intmax_t number;

	if (HH_FLAG)
		number = (signed char)va_arg(args, int);
	else if (H_FLAG)
		number = (short)va_arg(args, int);
	else if (L_FLAG)
		number = va_arg(args, long);
	else if (LL_FLAG)
		number = va_arg(args, long long);
	else
		number = va_arg(args, int);
	if (is_activated(flags) || PREC_FLAG)
		return (special_convert_int(number, fd, flags));
	else
	{
		if (number == -9223372036854775807 - 1)
			ft_putchar_fd('-', fd);
		ft_putnbr_fd(number, fd);
	}
	return (ft_nbrlen(number));
}
