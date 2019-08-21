/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:28:18 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 15:33:22 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int		ft_nbrlen(intmax_t n)
{
	int		nbdigits;

	nbdigits = 0;
	if (n == 0)
		return (1);
	if (n < nbdigits)
		nbdigits++;
	while (n != 0)
	{
		n = n / 10;
		nbdigits++;
	}
	return (nbdigits);
}
