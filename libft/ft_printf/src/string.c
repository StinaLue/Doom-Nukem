/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:29:53 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/14 10:07:49 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	special_convert_wstring(wchar_t *s, int len, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (MIN_FLAG)
	{
		if (len > 0 && s != NULL)
			ft_putwstr_fd(s, fd);
		else
			write(fd, "(null)", 6);
		full_len += pad_str(len, flags, fd);
		return (full_len + len);
	}
	full_len += pad_str(len, flags, fd);
	if (len > 0 && s != NULL)
		ft_putwstr_fd(s, fd);
	else
		write(fd, "(null)", 6);
	return (full_len + len);
}

int	special_convert_nullstring(int len, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision < len && flags->precision)
		len = flags->precision;
	else if (!flags->precision && (PREC_FLAG))
		len = 0;
	if (MIN_FLAG)
	{
		write(fd, "(null)", len);
		full_len += pad_str(len, flags, fd);
		return (full_len + len);
	}
	full_len += pad_str(len, flags, fd);
	write(fd, "(null)", len);
	return (full_len + len);
}

int	special_convert_string(char *s, int len, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision < len && flags->precision)
		len = flags->precision;
	else if (!flags->precision && (PREC_FLAG))
		len = 0;
	if (MIN_FLAG)
	{
		if (len > 0)
			write(fd, s, len);
		full_len += pad_str(len, flags, fd);
		return (full_len + len);
	}
	full_len += pad_str(len, flags, fd);
	if (len > 0)
		write(fd, s, len);
	return (full_len + len);
}

int	convert_wstring(va_list args, int fd, t_flags *flags)
{
	wchar_t	*s;
	int		len;

	s = va_arg(args, wchar_t *);
	if (s != NULL)
		len = ft_wstrlen(s);
	else
		len = 0;
	if (is_activated(flags))
		return (special_convert_wstring(s, len, fd, flags));
	if (s != NULL)
		ft_putwstr_fd(s, fd);
	else
		write(fd, "(null)", 6);
	return (len);
}

int	convert_string(va_list args, int fd, t_flags *flags)
{
	char	*s;
	int		len;

	if (L_FLAG)
		return (convert_wstring(args, fd, flags));
	s = va_arg(args, char *);
	if (s != NULL)
		len = ft_strlen(s);
	else
		len = 6;
	if (is_activated(flags) || (PREC_FLAG))
	{
		if (s != NULL)
			return (special_convert_string(s, len, fd, flags));
		else
			return (special_convert_nullstring(6, fd, flags));
	}
	if (s != NULL)
		write(fd, s, len);
	else
		write(fd, "(null)", 6);
	return (len);
}
