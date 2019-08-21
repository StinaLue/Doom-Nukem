/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:53:01 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 18:50:18 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	special_convert_wchar(wchar_t c, int fd, t_flags *flags)
{
	int full_len;
	int size;

	full_len = 0;
	size = ft_wcharlen(ft_nbits(c));
	if (MIN_FLAG)
	{
		full_len += ft_putwchar_fd(c, fd);
		full_len += pad_str(size, flags, fd);
		return (full_len);
	}
	full_len += pad_str(size, flags, fd);
	full_len += ft_putwchar_fd(c, fd);
	return (full_len);
}

int	special_convert_char(char c, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (MIN_FLAG)
	{
		ft_putchar_fd(c, fd);
		full_len += pad_str(1, flags, fd);
		return (full_len + 1);
	}
	if (PLUS_FLAG)
	{
		full_len += pad_str(1, flags, fd);
		ft_putchar_fd(c, fd);
		return (full_len + 1);
	}
	full_len += pad_str(1, flags, fd);
	ft_putchar_fd(c, fd);
	return (full_len + 1);
}

int	convert_wchar(va_list args, int fd, t_flags *flags)
{
	wchar_t	c;
	int		ret;

	ret = 0;
	c = va_arg(args, wint_t);
	if (is_activated(flags))
		return (special_convert_wchar(c, fd, flags));
	ret = ft_putwchar_fd(c, fd);
	return (ret);
}

int	convert_char(va_list args, int fd, t_flags *flags)
{
	char	c;
	int		ret;

	if (L_FLAG)
		return (convert_wchar(args, fd, flags));
	ret = 0;
	c = va_arg(args, int);
	if (is_activated(flags))
		return (special_convert_char(c, fd, flags));
	ft_putchar_fd(c, fd);
	return (1);
}
