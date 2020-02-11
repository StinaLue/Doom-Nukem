/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:43:12 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 21:15:44 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int		init_fonts(t_editor *editor)
{
	if ((editor->opt_menu.font_title =
		TTF_OpenFont("assets/fonts/dukes-3d.ttf", 16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if ((editor->instr_menu.font_title =
		TTF_OpenFont("assets/fonts/dukes-3d.ttf", 16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if ((editor->opt_menu.font =
		TTF_OpenFont("assets/fonts/dooM.ttf", 14)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if ((editor->instr_menu.font =
		TTF_OpenFont("assets/fonts/dooM.ttf", 16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	assign_sdlcolor(&editor->instr_menu.text_color, 255, 0, 0);
	assign_sdlcolor(&editor->opt_menu.text_color, 255, 0, 0);
	return (0);
}

int		init_alerts(t_editor *editor, SDL_Surface *surf)
{
	if ((editor->alert_convex_surf = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		"Sector has to be convex", editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->alert_convex_rect, create_vec((surf->w \
					- editor->alert_convex_surf->w) / 2, 0), create_vec(0, 0));
	if ((editor->alert_loading_surf = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		"Couldn't load (sector not finished or player not set)", \
			editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->alert_loading_rect, \
		create_vec((surf->w - editor->alert_loading_surf->w) / 2, 0), \
						create_vec(0, 0));
	if ((editor->loading_success_surf = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		"Loading map successful", editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->loading_success_rect, create_vec((surf->w - \
					editor->loading_success_surf->w) / 2, 0), create_vec(0, 0));
	return (0);
}

int		init_editor_menu(t_editor *editor)
{
	if (init_fonts(editor) != 0)
		return (1);
	if (init_instr_menu(editor, editor->instr_surf) != 0)
		return (1);
	if (init_options_menu(editor) != 0)
		return (1);
	if (init_alerts(editor, editor->editor_surf) != 0)
		return (1);
	return (0);
}
