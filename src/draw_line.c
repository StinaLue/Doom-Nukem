/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:06:42 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/14 17:15:45 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int		get_steps(double *x, double *y)
{
	int	steps;

	if (ft_absolute(*y) > ft_absolute(*x))
		return get_steps(y, x);
	else if (ft_absolute(*x) > 0)
	{
		steps = *x;
		*y = *y / ft_absolute(*x);
		*x = *x / ft_absolute(*x);
		return (steps);
	}
	return (0);
}

void	draw_line(const t_vec a, const t_vec b, SDL_Surface *surf, int color)
{
	double	deltax;
	double	deltay;
	t_vecdb	pos;
	int		steps;

	deltax = b.x - a.x;
	deltay = b.y - a.y;
	steps = ft_absolute(get_steps(&deltax, &deltay));
	pos.x = a.x + 0.5;
	pos.y = a.y + 0.5;
	while (steps >= 0)
	{
		fill_pix(surf, (int)pos.x, (int)pos.y, color);
		pos.x += deltax;
		pos.y += deltay;
		steps--;
	}
}
