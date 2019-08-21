/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:59:15 by afonck            #+#    #+#             */
/*   Updated: 2018/11/13 16:11:06 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

static void	putdis(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putnbr_fd(intmax_t n, int fd)
{
	if (n < -9223372036854775807)
	{
		ft_putnbr_fd(9223372036, fd);
		ft_putnbr_fd(854775808, fd);
	}
	else
	{
		if (n < 0)
		{
			putdis(('-'), fd);
			n = -n;
		}
		if (n >= 10)
		{
			ft_putnbr_fd((n / 10), fd);
			ft_putnbr_fd((n % 10), fd);
		}
		else
		{
			putdis(('0' + n), fd);
		}
	}
}
