/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_surfaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:55:47 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/06 13:07:58 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	create_surfaces_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	if ((editor->editor_surf = SDL_CreateRGBSurface(0, sdlmain->win_surf->w / 1.79, sdlmain->win_surf->h, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", SDL_GetError()));
	if ((editor->opt_surf = SDL_CreateRGBSurface(0, sdlmain->win_surf->w - (sdlmain->win_surf->w / 1.79), (sdlmain->win_surf->h / 3) * 2, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", SDL_GetError())); // remove bug color from game shining through editor on right side
	if ((editor->instr_surf = SDL_CreateRGBSurface(0, sdlmain->win_surf->w - (sdlmain->win_surf->w / 1.79), sdlmain->win_surf->h - (sdlmain->win_surf->h / 3) * 2, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", SDL_GetError()));
	assign_sdlrect(&editor->editor_rect, create_vec(0, 0), create_vec(sdlmain->win_surf->w / 1.79, sdlmain->win_surf->h));
	assign_sdlrect(&editor->options_rect, create_vec(sdlmain->win_surf->w / 1.79, 0), create_vec(sdlmain->win_surf->w - (sdlmain->win_surf->w / 1.79), (sdlmain->win_surf->h / 3) * 2));
	assign_sdlrect(&editor->instr_rect, create_vec(sdlmain->win_surf->w / 1.79, (sdlmain->win_surf->h / 3) * 2), create_vec(sdlmain->win_surf->w - (sdlmain->win_surf->w / 1.79), sdlmain->win_surf->h - ((sdlmain->win_surf->h / 3) * 2)));
	return(0);
}