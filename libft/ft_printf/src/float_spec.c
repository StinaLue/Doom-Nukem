/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:00:04 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/06 15:02:12 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	flags_spec(t_flags *flags, int nbpad, int fd, intmax_t number)
{
	if (!(MIN_FLAG))
		pad_space(nbpad, fd);
	if ((PLUS_FLAG) && number >= 0)
		ft_putchar_fd('+', fd);
	if ((SPACE_FLAG) && number >= 0 && !(PLUS_FLAG))
		ft_putchar_fd(' ', fd);
}

void	flags_specfloat(t_flags *flags, int nbpad, int fd, double number)
{
	if (!(MIN_FLAG))
	{
		if ((PLUS_FLAG) && number >= 0 && ZERO_FLAG && (1 / number > 0))
			ft_putchar_fd('+', fd);
		if ((SPACE_FLAG) && number >= 0 && !(PLUS_FLAG)
				&& ZERO_FLAG && (1 / number > 0))
			ft_putchar_fd(' ', fd);
		if (ZERO_FLAG)
			pad_zero(nbpad, fd);
		else
			pad_space(nbpad, fd);
		if ((PLUS_FLAG) && number >= 0 && !(ZERO_FLAG) && (1 / number > 0))
			ft_putchar_fd('+', fd);
		if ((SPACE_FLAG) && number >= 0 && !(PLUS_FLAG)
				&& !(ZERO_FLAG) && (1 / number > 0))
			ft_putchar_fd(' ', fd);
	}
	else
	{
		if ((PLUS_FLAG) && number >= 0 && (1 / number > 0))
			ft_putchar_fd('+', fd);
		if ((SPACE_FLAG) && number >= 0 && !(PLUS_FLAG) && (1 / number > 0))
			ft_putchar_fd(' ', fd);
	}
}

void	print_float(double number, int preclen, t_flags *flags, int fd)
{
	if (number == 0 && !(1 / number > 0) && !(ZERO_FLAG))
		ft_putchar_fd('-', fd);
	if (ZERO_FLAG || (number == 0 && !(1 / number > 0)))
		ft_ftoa_fd(ft_absfloat(number), preclen, fd);
	else
		ft_ftoa_fd(number, preclen, fd);
}

int		pad_float_prec(double number, int preclen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;
	int nbrlen;

	nbrlen = ft_floatlen(number, preclen) - (!(1 / number > 0) ? 1 : 0) +
		((HASH_FLAG) && (PREC_FLAG) && flags->precision == 0);
	nbpad = flags->field_width - (flags->precision >= nbrlen ?
			flags->precision : nbrlen) - !(1 / number > 0) -
		((PLUS_FLAG || SPACE_FLAG) && (1 / number > 0));
	nbpad = (nbpad < 0 ? 0 : nbpad);
	nbzero = (flags->precision >= nbrlen ? flags->precision : nbrlen) - nbrlen
		+ ((HASH_FLAG) && (PREC_FLAG) && flags->precision == 0);
	padlen = nbpad + nbzero + ((1 / number > 0) ?
			(PLUS_FLAG) || (SPACE_FLAG) : 0);
	if (number == 0 && !(1 / number > 0) && (ZERO_FLAG))
		ft_putchar_fd('-', fd);
	flags_specfloat(flags, nbpad, fd, number);
	print_float(number, preclen, flags, fd);
	if ((HASH_FLAG) && (PREC_FLAG) && flags->precision == 0)
		ft_putchar_fd('.', fd);
	if ((MIN_FLAG))
		pad_space(nbpad, fd);
	return (padlen);
}
