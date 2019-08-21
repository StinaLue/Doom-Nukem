/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floatlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:20:50 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 15:30:00 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_floatlen(double n, int afterpoint)
{
	int		len;
	long	ipart;
	double	fpart;

	len = 0;
	ipart = (long)n;
	fpart = n - (double)ipart;
	fpart = fpart * ft_pow(10, afterpoint);
	fpart = (n >= 0 ? fpart + 0.5 : fpart - 0.5);
	len += ft_nbrlen(ipart);
	if (afterpoint != 0)
		len += afterpoint + 1;
	if (ipart == 0 && !(1 / n > 0))
		len++;
	return (len);
}
