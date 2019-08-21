/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checklen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 09:44:59 by afonck            #+#    #+#             */
/*   Updated: 2019/07/05 12:34:18 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	store_field_width(const char **fmt, t_flags *flags)
{
	char	field_width[10];
	int		i;

	i = 0;
	ft_bzero((void *)field_width, 10);
	while (ft_isdigit(**fmt) && i < 10)
	{
		field_width[i] = **fmt;
		i++;
		(*fmt)++;
	}
	while (ft_isdigit(**fmt))
		(*fmt)++;
	flags->field_width = (ft_atoi(field_width) > 0 ? ft_atoi(field_width) : 0);
	ft_bzero((void *)field_width, 10);
}

void	check_field_width(const char **fmt, t_flags *flags)
{
	if (!ft_isdigit(**fmt))
		return ;
	store_field_width(fmt, flags);
}

void	store_precision(const char **fmt, t_flags *flags)
{
	char	precision[10];
	int		i;

	i = 0;
	ft_bzero((void *)precision, 10);
	while ((ft_isdigit(**fmt) || is_flag(**fmt)) && i < 10)
	{
		precision[i] = **fmt;
		i++;
		(*fmt)++;
	}
	while (ft_isdigit(**fmt))
		(*fmt)++;
	flags->precision = (ft_atoi(precision) > 0 ? ft_atoi(precision) : 0);
	ft_bzero((void *)precision, 10);
}

void	check_precision(const char **fmt, t_flags *flags)
{
	if (**fmt == '.')
	{
		flags->state |= PREC;
		(*fmt)++;
		store_precision(fmt, flags);
	}
}
