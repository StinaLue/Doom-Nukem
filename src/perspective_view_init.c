/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:00:48 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/12 11:09:38 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			base_values_dspwall(t_display_wall *display, double wall_len, \
				SDL_Surface *tex, t_view *old_view)
{
	display->dist_left = display->intersect.a.y;
	display->dist_right = display->intersect.b.y;
	display->length = wall_len;
	display->texture = tex;
	display->top_limit = old_view->top_limit;
	display->bot_limit = old_view->bot_limit;
}

void			init_display_wall(t_display_wall *display, \
		t_wall_node *current_wall, t_view old_view, SDL_Surface **wall_textures)
{
	double	len;

	base_values_dspwall(display, current_wall->length, \
	wall_textures[current_wall->tex_index], &old_view);
	if (fabs(display->relative.a.x - display->relative.b.x) > 0.001)
	{
		len = display->relative.b.x - display->relative.a.x;
		display->start_pos = \
			(display->intersect.a.x - display->relative.a.x) / len;
		display->end_pos = \
			(display->intersect.b.x - display->relative.a.x) / len;
	}
	else if (fabs(display->relative.a.y - display->relative.b.y) > 0.001)
	{
		len = display->relative.b.y - display->relative.a.y;
		display->start_pos = \
				(display->intersect.a.y - display->relative.a.y) / len;
		display->end_pos = \
				(display->intersect.b.y - display->relative.a.y) / len;
	}
	else
	{
		display->start_pos = 0;
		display->end_pos = 1;
	}
}
