/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:01:04 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/12 11:06:19 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	gettexx(double x, t_display_wall *dsp)
{
	double	top_div;
	double	bot_div;

	top_div = (1 - x) * dsp->start_pos / dsp->dist_left \
				+ x * dsp->end_pos / dsp->dist_right;
	bot_div = (1 - x) * 1 / dsp->dist_left + x * 1 / dsp->dist_right;
	x = top_div / bot_div;
	return (x);
}

double	gettexy(double y, int top, int bot)
{
	y -= bot;
	y /= top - bot;
	return (y);
}

int		gettexc(double x, double y, t_display_wall *dsp, SDL_Surface *tex)
{
	int	truex;
	int	truey;
	int	color;

	if (dsp->texture_ratio > 1)
		x = fmod(x * (int)dsp->texture_ratio, 1);
	else
		y = fmod(y * (int)(1 / dsp->texture_ratio), 1);
	dsp = NULL;
	truex = fmod(fabs(x * (tex->w - 1)), tex->w);
	truey = fmod((tex->h - 1) - fabs(y * (tex->h - 1)), tex->h);
	color = ((int *)tex->pixels)[truex + truey * tex->w];
	return (color);
}

t_vecdb	set_draw_limits(t_display_wall *dsp)
{
	t_vecdb limit;

	limit.x = dsp->top_left.y + 0.5;
	limit.y = dsp->bottom_left.y + 0.5;
	return (limit);
}

void	draw_texture(SDL_Surface *surf, SDL_Surface *tex, \
							t_display_wall *dsp, int type)
{
	int		width;
	t_vecdb	delta;
	t_vec	win;
	t_vecdb	pos;
	t_vecdb	limit;

	width = dsp->top_right.x - dsp->top_left.x;
	delta.x = (double)(dsp->top_right.y - dsp->top_left.y) / width;
	delta.y = (double)(dsp->bottom_right.y - dsp->bottom_left.y) / width;
	win.x = dsp->top_left.x - 1;
	limit = set_draw_limits(dsp);
	while (++win.x < dsp->top_right.x)
	{
		pos.x = gettexx((double)(win.x - dsp->top_left.x) / width, dsp);
		win.y = limit.x > dsp->top_limit ? dsp->top_limit : limit.x;
		fill_ceiling(surf, win, dsp->top_limit, type);
		if (limit.x > limit.y)
			while (win.y >= limit.y && win.y >= dsp->bot_limit)
				fill_pix(surf, win.x, win.y--, gettexc(pos.x, \
							gettexy(win.y, limit.x, limit.y), dsp, tex));
		win.y = limit.y;
		fill_floor(surf, win, dsp->bot_limit, type);
		limit.x += delta.x;
		limit.y += delta.y;
	}
}
