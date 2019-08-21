/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:18:12 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/08 15:21:37 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	check_color(const char **fmt, t_flags *flags)
{
	if (**fmt == '{')
	{
		(*fmt)++;
		if (**fmt == 'r')
			flags->color = 1;
		else if (**fmt == 'g')
			flags->color = 2;
		else if (**fmt == 'y')
			flags->color = 3;
		else if (**fmt == 'b')
			flags->color = 4;
		else if (**fmt == 'm')
			flags->color = 5;
		else if (**fmt == 'c')
			flags->color = 6;
		(*fmt)++;
		if (**fmt == '}')
			(*fmt)++;
		else
			flags->color = 0;
	}
}

void	choose_color(int fd, int color)
{
	if (color == 1)
		write(fd, RED, COLORLEN);
	else if (color == 2)
		write(fd, GREEN, COLORLEN);
	else if (color == 3)
		write(fd, YELLOW, COLORLEN);
	else if (color == 4)
		write(fd, BLUE, COLORLEN);
	else if (color == 5)
		write(fd, MAGENTA, COLORLEN);
	else if (color == 6)
		write(fd, CYAN, COLORLEN);
}
