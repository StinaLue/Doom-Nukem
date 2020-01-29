/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:01:04 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/27 18:39:36 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


int	limit_value2(int value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}

void draw_vertical_tex(t_vec top, t_vec bottom, SDL_Surface *surf, SDL_Surface *tex, int x)
{
	int color;
	double current_ytex = 0;

	top.y = limit_value2(top.y, 0, surf->h - 1);
	bottom.y = limit_value2(bottom.y, 0, surf->h - 1);
	double step;
	if (top.y - bottom.y != 0)
		step = 1.0 * tex->h / (top.y - bottom.y);
	else
		step = tex->h;
	if (step < 1)
		step = 1;
	//printf("current step %f\n", step);
	while (top.y >= bottom.y)
	{
		color = ((Uint32 *)tex->pixels)[(int)current_ytex + x];
		fill_pix(surf, top.x, top.y, color);
		top.y--;
		//current_ytex++;
		current_ytex += step;
	}
}

void	fill_wall_texture(SDL_Surface *surf, const t_wall3d *display_wall, SDL_Surface *tex)
{
	double x;
	t_vec current_top;
	t_vec current_bottom;
	//int current_xtex = display_wall->bottom_left.x;
	int current_xtex = 0;
	double step;
	if (display_wall->top_right.x - display_wall->top_left.x == 0)
		step = tex->w;
	else
		step = tex->w / (display_wall->top_right.x - display_wall->top_left.x);
	if (step < 1)
		step = 1;
	//printf("step %f\n", step);
	//printf("display_wall x %d bottom right | x %d bottom left\n", display_wall->bottom_left.x, display_wall->bottom_right.x);

	if (display_wall->top_left.x < display_wall->top_right.x)
	{
		x = display_wall->top_left.x;
		while (x < display_wall->top_right.x)
		{
			current_top.y = display_wall->top_left.y + (x - display_wall->top_left.x) * (long)(display_wall->top_right.y - display_wall->top_left.y) / (abs(display_wall->top_right.x - display_wall->top_left.x) == 0 ? 1 : (display_wall->top_right.x - display_wall->top_left.x));
			current_bottom.y = display_wall->bottom_left.y + (x - display_wall->top_left.x) * (long)(display_wall->bottom_right.y - display_wall->bottom_left.y) / (abs(display_wall->top_right.x - display_wall->top_left.x) ==0 ? 1 : (display_wall->top_right.x - display_wall->top_left.x));
			current_top.x = x;
			current_bottom.x = x;
			draw_vertical_tex(current_top, current_bottom, surf, tex, current_xtex * tex->h);
			x++;
			//current_xtex++;
			current_xtex += step;
			if (current_xtex > tex->w)
				current_xtex = 0;
		}
	}
}

double	get_texture_x(int x, t_wall3d *wall)
{
	double	proportional_x;
	double	wall_true_length;
	
	proportional_x = ((double)x - wall->top_left.x) / (wall->top_right.x - wall->top_left.x);
	wall_true_length = 1 - (wall->start_pos + wall->end_pos);
	proportional_x *= wall_true_length;
	proportional_x += wall->start_pos;
	 
	return (proportional_x);
}

int		get_tex_color(double x, double y, SDL_Surface *tex)
{
	int	truex;
	int	truey;
	int	color;

	truex = x * tex->w;
	truey = y * tex->h;
	color = ((Uint32 *)tex->pixels)[truex + truey * tex->w];
	color &= 0xFFFFFF;

	return color;
}

double	get_texture_y(double y, int top, int bot)
{
	double	proportional_y;

	proportional_y = y - bot;
	proportional_y /= (top - bot);
	return (proportional_y);
}

void	draw_texture(SDL_Surface *surf, SDL_Surface *tex, t_wall3d *wall)
{
	int		width;
	double	delta;
	double	top_limit;
	double	bot_limit;
	int		x;
	double	y;
	Uint32	color = 0;
	double	tex_x;
	double	tex_y;

	width = wall->top_right.x - wall->top_left.x;
	if (width <= 0)
		return ;
	delta = (double)(wall->top_left.y - wall->top_right.y) / width;

	top_limit = wall->top_left.y + 0.5;
	bot_limit = wall->bottom_left.y - 0.5;
	x = wall->top_left.x;
	while (x <= wall->top_right.x)
	{
		tex_x = get_texture_x(x, wall);

		if (top_limit < surf->h)
			y = (int)top_limit;
		else
			y = surf->h - 1;
		while (y >= bot_limit && y >= 0)
		{
			tex_y = get_texture_y(y, top_limit, bot_limit);
			color = get_tex_color(tex_x, tex_y, tex);
			fill_pix(surf, x, (int)y, color);
			y--;
		}
		top_limit -= delta;
		bot_limit += delta;
		x++;
	}
	tex = NULL;
}