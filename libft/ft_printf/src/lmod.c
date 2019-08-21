/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:29:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/08 15:32:48 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	activate_biglmod(const char **fmt, t_flags *flags)
{
	(*fmt)++;
	flags->state |= BIGL;
}

void	check_lmod(const char **fmt, t_flags *flags)
{
	if (**fmt == 'h')
	{
		(*fmt)++;
		if (**fmt == 'h')
		{
			flags->state |= HH;
			(*fmt)++;
		}
		else
			flags->state |= H;
	}
	else if (**fmt == 'l')
	{
		(*fmt)++;
		if (**fmt == 'l')
		{
			flags->state |= LL;
			(*fmt)++;
		}
		else
			flags->state |= L;
	}
	else if (**fmt == 'L')
		activate_biglmod(fmt, flags);
}
