/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:06:42 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/20 18:00:12 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int		get_steps(double *x, double *y)
{
	int	steps;

	if (fabs(*y) > fabs(*x))
		return get_steps(y, x);
	else if (fabs(*x) > 0)
	{
		steps = *x;
		*y = *y / fabs(*x);
		*x = *x / fabs(*x);
		return (steps);
	}
	return (0);
}

void	draw_line(t_vec a, t_vec b, SDL_Surface *surf, int color)
{
	double	deltax;
	double	deltay;
	t_vecdb	pos;
	int		steps;

	if (b.y < a.y)
	{
		draw_line(b, a, surf, color);
		return ;
	}

	if (b.y < 0 || a.y > surf->h)
		return ;
	if (b.y > surf->h)
	{
		b.x -= ((double)b.x - a.x) / (((double)b.y - a.y) / ((double)b.y - surf->h));
		b.y = surf->h;
	}
	if (a.y < 0)
	{
		a.x += ((double)b.x - a.x) / (((double)b.y - a.y) / -a.y);
		a.y = 0;
	}

	deltax = b.x - a.x;
	deltay = b.y - a.y;
	steps = ft_absolute(get_steps(&deltax, &deltay));
	pos.x = a.x + 0.5;
	pos.y = a.y + 0.5;
	while (steps >= 0)
	{
		if (pos.x > 0 && pos.y > 0 && pos.x < surf->w && pos.y < surf->h)
			fill_pix(surf, (int)pos.x, (int)pos.y, color);
		pos.x += deltax;
		pos.y += deltay;
		steps--;
	}
}
