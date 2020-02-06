/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_surfaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:55:47 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/06 14:31:18 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	create_surfaces_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	SDL_Surface *win;

	win = sdlmain->win_surf;
	if ((editor->editor_surf = SDL_CreateRGBSurface(0, win->w / 1.79, win->h, \
		32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", \
					SDL_GetError()));
		if ((editor->opt_surf = SDL_CreateRGBSurface(0, win->w - \
		(win->w / 1.79), (win->h / 3) * 2, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", \
				SDL_GetError()));
		if ((editor->instr_surf = SDL_CreateRGBSurface(0, win->w \
			- (win->w / 1.79), win->h - (win->h / 3) * 2, \
			32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", \
				SDL_GetError()));
		assign_sdlrect(&editor->editor_rect, create_vec(0, 0), \
			create_vec(win->w / 1.79, win->h));
	assign_sdlrect(&editor->options_rect, create_vec(win->w / 1.79, 0), \
		create_vec(win->w - (win->w / 1.79), (win->h / 3) * 2));
	assign_sdlrect(&editor->instr_rect, create_vec(win->w / 1.79, \
				(win->h / 3.2) * 2), create_vec(win->w - (win->w / 1.79), \
				win->h - ((win->h / 3.2) * 2)));
	return (0);
}
