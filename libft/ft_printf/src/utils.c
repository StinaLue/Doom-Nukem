/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:41:48 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/14 10:33:42 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill_buf(char c, int nbfill, char *buf)
{
	int i;

	i = 0;
	while (nbfill > 0)
	{
		buf[i] = c;
		i++;
		nbfill--;
	}
}

void	pad_zero(int nbzero, int fd)
{
	char buf[101];

	if (nbzero > 0)
	{
		while (nbzero > 0)
		{
			if (nbzero < 100)
			{
				fill_buf('0', nbzero, buf);
				write(fd, buf, nbzero);
				return ;
			}
			fill_buf('0', 100, buf);
			write(fd, buf, 100);
			nbzero -= 100;
		}
	}
}

void	pad_space(int nbpad, int fd)
{
	char buf[101];

	if (nbpad > 0)
	{
		while (nbpad > 0)
		{
			if (nbpad < 100)
			{
				fill_buf(' ', nbpad, buf);
				write(fd, buf, nbpad);
				return ;
			}
			fill_buf(' ', 100, buf);
			write(fd, buf, 100);
			nbpad -= 100;
		}
	}
}

int		is_flag(char c)
{
	if (c == '#' || c == '-' || c == '+' || c == ' ' || c == '0')
		return (1);
	else
		return (0);
}
