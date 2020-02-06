/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:01:04 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/05 16:43:00 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	get_texture_x(double x, t_wall3d *wall)
{
	double	top_div;
	double	bot_div;

	top_div = (1-x) * wall->start_pos/wall->dist_left + x * wall->end_pos/wall->dist_right;
	bot_div = (1-x) * 1/wall->dist_left + x * 1/wall->dist_right;
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

	if (fabs(x) > 1)
		x = fmod(x, 1);
	if (fabs(y) > 1)
		x = fmod(y, 1);
	truex = x * (tex->w - 1);
	truey = y * (tex->h - 1);

	color = ((Uint32 *)tex->pixels)[truex + truey * tex->w];
	color &= 0xFFFFFF;

	return color;
}

void	draw_texture(SDL_Surface *surf, SDL_Surface *tex, t_wall3d *wall)
{
	int		width;
	double	delta;
	double	top_limit;
	double	bot_limit;
	t_vec	win;
	t_vecdb	pos;

	width = wall->top_right.x - wall->top_left.x + 1;
	if (width <= 1)
		return ;
	delta = (double)(wall->top_left.y - wall->top_right.y) / (width - 1);

	top_limit = wall->top_left.y + 0.5;
	bot_limit = wall->bottom_left.y + 0.5;
	win.x = wall->top_left.x;
	//while (win.x <= wall->top_right.x)
	while (win.x < wall->top_right.x)
	{
		pos.x = get_texture_x((double)(win.x - wall->top_left.x) / width, wall);
		//pos.x *= (int)(wall->length / 20 + 1);
		if (top_limit < surf->h)
			win.y = top_limit;
		else
			win.y = surf->h - 1;
		while (win.y >= bot_limit && win.y >= 0)
		{
			pos.y = get_texture_y(win.y, top_limit, bot_limit);
			if (win.x < 0 || win.x >= surf->w || win.y < 0 || win.y >= surf->h)
				printf("pixel outside of screen\n");
			fill_pix(surf, win.x, win.y, get_tex_color(pos.x, pos.y, tex));
			win.y--;
		}
		top_limit -= delta;
		bot_limit += delta;
		win.x++;
	}
}