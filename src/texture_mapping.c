/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:01:04 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/07 15:28:30 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	get_texture_x(double x, t_display_wall *dsp)
{
	double	top_div;
	double	bot_div;

	top_div = (1-x) * dsp->start_pos/dsp->dist_left + x * dsp->end_pos/dsp->dist_right;
	bot_div = (1-x) * 1/dsp->dist_left + x * 1/dsp->dist_right;
	x = top_div / bot_div;
	return (x);
}

double	get_texture_y(double y, int top, int bot)
{
	y -= bot;
	y /= top - bot;
	return (y);
}

int		get_tex_color(double x, double y, SDL_Surface *tex)
{
	int	truex;
	int	truey;
	int	color;

	truex = fmod(fabs(x * (tex->w - 1)), tex->w);
	truey = fmod((tex->h - 1) - fabs(y * (tex->h - 1)), tex->h);
	color = ((int *)tex->pixels)[truex + truey * tex->w];

	return color;
}

void	draw_texture(SDL_Surface *surf, SDL_Surface *tex, t_display_wall *dsp)
{
	int		width;
	double	delta_top;
	double	delta_bot;
	t_vec	win;
	t_vecdb	pos;
	double	top;
	double	bot;

	width = dsp->top_right.x - dsp->top_left.x;
	if (width < 1)
		return ;
	delta_top = (double)(dsp->top_right.y - dsp->top_left.y) / width;
	delta_bot = (double)(dsp->bottom_right.y - dsp->bottom_left.y) / width;

	win.x = dsp->top_left.x;
	top = dsp->top_left.y + 0.5;
	bot = dsp->bottom_left.y + 0.5;
	while (win.x < dsp->top_right.x)
	{
		pos.x = get_texture_x((double)(win.x - dsp->top_left.x) / width, dsp);
		if (top > dsp->top_limit)
			win.y = dsp->top_limit;
		else
			win.y = top;
		while (win.y >= bot && win.y >= dsp->bot_limit)
		{
			pos.y = get_texture_y(win.y, top, bot);
			if (win.x < 0 || win.x >= surf->w || win.y < 0 || win.y >= surf->h)
				printf("pixel outside of screen\n");
			fill_pix(surf, win.x, win.y, get_tex_color(pos.x, pos.y, tex));
			win.y--;
		}
		top += delta_top;
		bot += delta_bot;
		win.x++;
	}
}