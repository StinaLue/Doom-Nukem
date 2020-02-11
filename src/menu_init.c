/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 20:57:28 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 20:58:37 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_menu_surfs(t_menu *menu, t_sdlmain *sdlmain, SDL_Surface *surf)
{
	if ((menu->menu_title = \
		TTF_RenderText_Solid(sdlmain->font, "MENU", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		if ((menu->options[0] = TTF_RenderText_Solid(sdlmain->font, \
				"editor", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		if ((menu->options[1] = TTF_RenderText_Solid(sdlmain->font, \
				"return to game", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		if ((menu->options[2] = TTF_RenderText_Solid(sdlmain->font, \
				"resize window", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		if ((menu->options[3] = TTF_RenderText_Solid(sdlmain->font, \
				"quit game", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		if ((menu->background = SDL_CreateRGBSurface(0, surf->w \
		- (surf->w / 8), surf->h - (surf->h / 4), 32, 0, 0, 0, 0)) == NULL)
		return (error_return("SDL_CreateRGBSurface error = %s\n", \
			SDL_GetError()));
		return (0);
}

int		init_menu(t_menu *menu, t_sdlmain *sdlmain)
{
	menu->current_option = 0;
	menu->prev_option = 0;
	menu->previous_state = QUIT_STATE;
	menu->background = NULL;
	assign_sdlcolor(&menu->text_color, 255, 0, 0);
	assign_sdlrect(&menu->background_rect, create_vec((sdlmain->win_surf->w \
				/ 8) / 2, (sdlmain->win_surf->h / 4) / 2), create_vec(0, 0));
	if (init_menu_surfs(menu, sdlmain, sdlmain->win_surf) != 0)
		return (1);
	assign_sdlrect(&menu->menu_title_rect, \
			create_vec((menu->background->w - menu->menu_title->w) / 2, \
			(menu->background->h - menu->menu_title->h) / 8), create_vec(0, 0));
	assign_sdlrect(&menu->options_rects[1], \
			create_vec((menu->background->w - menu->options[1]->w) / 2, \
			(menu->background->h - menu->options[1]->h) / 2), create_vec(0, 0));
	assign_sdlrect(&menu->options_rects[0], \
			create_vec((menu->background->w - menu->options[0]->w) / 2, \
			menu->options_rects[1].y - menu->options[1]->h), create_vec(0, 0));
	assign_sdlrect(&menu->options_rects[2], \
			create_vec((menu->background->w - menu->options[2]->w) / 2, \
			menu->options_rects[1].y + menu->options[1]->h), create_vec(0, 0));
	assign_sdlrect(&menu->options_rects[3], \
			create_vec((menu->background->w - menu->options[3]->w) / 2, \
			menu->options_rects[2].y + menu->options[2]->h), create_vec(0, 0));
	return (0);
}
