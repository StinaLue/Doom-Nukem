/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view_portals.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:58:30 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/12 11:09:29 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void			draw_portal_untextured(t_display_wall *win, \
				SDL_Surface *surf)
{
	draw_line(win->top_left, win->top_right, surf, 0xff8800);
	draw_line(win->top_right, win->bottom_right, surf, 0xffff00);
	draw_line(win->bottom_right, win->bottom_left, surf, 0x88ff00);
	draw_line(win->bottom_left, win->top_left, surf, 0xffff00);
}

void			draw_portal(t_display_wall *wall, \
					t_display_wall *window, SDL_Surface *surf)
{
	t_vec	tmp_values;

	tmp_values.x = window->bottom_left.y;
	tmp_values.y = window->bottom_right.y;
	window->bottom_left.y = window->top_left.y;
	window->bottom_right.y = window->top_right.y;
	window->top_left.y = wall->top_left.y;
	window->top_right.y = wall->top_right.y;
	if (ft_strncmp(surf->userdata, "textured", 8) != 0)
		draw_portal_untextured(window, surf);
	else
		draw_texture(surf, window->texture, window, 1);
	window->top_left.y = tmp_values.x;
	window->top_right.y = tmp_values.y;
	window->bottom_left.y = wall->bottom_left.y;
	window->bottom_right.y = wall->bottom_right.y;
	if (ft_strncmp(surf->userdata, "textured", 8) != 0)
		draw_portal_untextured(window, surf);
	else
		draw_texture(surf, window->texture, window, 2);
}
