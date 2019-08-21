/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:12:16 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/08 15:13:03 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

t_flags		*init_flags(void)
{
	t_flags *flags;

	if ((flags = (t_flags *)malloc(sizeof(t_flags))) == NULL)
		return (NULL);
	flags->state = 0;
	flags->field_width = 0;
	flags->precision = 0;
	flags->color = 0;
	return (flags);
}

void		check_flags(const char **fmt, t_flags *flags)
{
	while (is_flag(**fmt))
	{
		activate_flags(flags, **fmt);
		(*fmt)++;
	}
}

void		activate_flags(t_flags *flags, char c)
{
	if (c == '#')
		flags->state |= HASHTAG;
	else if (c == '-')
		flags->state |= MINUS;
	else if (c == '+')
		flags->state |= PLUS;
	else if (c == ' ')
		flags->state |= SPACE;
	else if (c == '0')
		flags->state |= ZERO;
	else
		return ;
}

int			is_activated(t_flags *flags)
{
	if ((HASH_FLAG) || (MIN_FLAG) || (PLUS_FLAG)
			|| (SPACE_FLAG) || (ZERO_FLAG)
			|| flags->field_width || flags->precision)
		return (1);
	return (0);
}

void		flush_flags(t_flags *flags)
{
	flags->state = 0;
	flags->field_width = 0;
	flags->precision = 0;
	flags->color = 0;
}
