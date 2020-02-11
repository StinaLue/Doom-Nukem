/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_main_surfaces.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:55:47 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 10:36:44 by sluetzen         ###   ########.fr       */
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
		(win->w / 1.79) + 1, (win->h / 3) * 2, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", \
				SDL_GetError()));
		if ((editor->instr_surf = SDL_CreateRGBSurface(0, win->w \
			- (win->w / 1.79) + 1, win->h - (win->h / 3) * 2, \
			32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", \
				SDL_GetError()));
		assign_sdlrect(&editor->editor_rect, create_vec(0, 0), \
			create_vec(win->w / 1.79, win->h));
	assign_sdlrect(&editor->options_rect, create_vec(win->w / 1.79, 0), \
		create_vec(win->w - (win->w / 1.79), (win->h / 3) * 2));
	assign_sdlrect(&editor->instr_rect, create_vec(win->w / 1.79, \
				(win->h / 3) * 2), create_vec(win->w - (win->w / 1.79), \
				win->h - ((win->h / 3) * 2)));
	return (0);
}

int	blit_editor_surf(t_editor *editor, t_sdlmain *sdlmain)
{
	if ((SDL_BlitSurface(editor->editor_surf, NULL,
			sdlmain->win_surf, &editor->editor_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n",
				SDL_GetError()));
		if ((SDL_BlitSurface(editor->opt_surf, NULL,
		sdlmain->win_surf, &editor->options_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n",
				SDL_GetError()));
		if ((SDL_BlitSurface(editor->instr_surf, NULL,
		sdlmain->win_surf, &editor->instr_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	if (sdlmain->mouse_pos.x * editor->offset < editor->editor_surf->w)
	{
		if ((SDL_BlitScaled(editor->wall_textures[editor->opt_menu.activ_tex], \
				NULL, sdlmain->win_surf, &editor->mouse_rect)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", \
					SDL_GetError()));
	}
	return (0);
}
