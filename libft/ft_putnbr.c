/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:35:53 by afonck            #+#    #+#             */
/*   Updated: 2018/11/13 16:10:39 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	putdis(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putnbr(-21474);
		ft_putnbr(83648);
	}
	else
	{
		if (n < 0)
		{
			putdis('-');
			n = -n;
		}
		if (n >= 10)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else
		{
			putdis('0' + n);
		}
	}
}
