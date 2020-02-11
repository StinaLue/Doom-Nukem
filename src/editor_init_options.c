/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:41:57 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 11:52:49 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	set_height(t_options_menu *menu, SDL_Surface *surf)
{
	int height;
	int width;

	height = surf->h / 20;
	width = surf->w / 16;
	assign_sdlrect(&menu->height_rect[0], create_vec(height * 7, height * 5), \
					create_vec((surf->w) / 7, (surf->w) / 11));
	assign_sdlrect(&menu->height_rect[1], create_vec(height * 7, height * 6), \
					create_vec((surf->w) / 7, (surf->w) / 11));
}

void	set_textures(SDL_Rect *text_rect, SDL_Surface *surf)
{
	int h;
	int w;

	h = surf->h / 20;
	w = surf->w / 16;
	assign_sdlrect(&text_rect[0], create_vec(h, h * 10), create_vec(w, w));
	assign_sdlrect(&text_rect[1], create_vec(h, h * 12), create_vec(w, w));
	assign_sdlrect(&text_rect[2], create_vec(h, h * 14), create_vec(w, w));
	assign_sdlrect(&text_rect[3], create_vec(h * 3, h * 10), create_vec(w, w));
	assign_sdlrect(&text_rect[4], create_vec(h * 3, h * 12), create_vec(w, w));
	assign_sdlrect(&text_rect[5], create_vec(h * 3, h * 14), create_vec(w, w));
	assign_sdlrect(&text_rect[6], create_vec(h * 5, h * 10), create_vec(w, w));
	assign_sdlrect(&text_rect[7], create_vec(h * 5, h * 12), create_vec(w, w));
	assign_sdlrect(&text_rect[8], create_vec(h * 5, h * 14), create_vec(w, w));
	//assign_sdlrect(&text_rect[9], create_vec((h) * 7, (h) * 10), create_vec(w, w));
	//assign_sdlrect(&text_rect[10], create_vec((h) * 7, (h) * 12), create_vec(w, w));
	//assign_sdlrect(&text_rect[11], create_vec((h) * 7, (h) * 14), create_vec(w, w));
}

int		init_choose_opt_menu(t_editor *editor, int surf_h, int surf_w)
{
	if (create_opt_str(editor, create_vec(surf_h, surf_h * 3), \
										0, "CHOOSE HEIGHT") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_h, surf_h * 8.5), \
										1, "CHOOSE TEXTURE") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_w, surf_h * 3), \
										2, "LOAD/SAVE MAP") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_w, surf_h * 8.5), \
										3, "CHOOSE MUSIC") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_w, surf_h * 13), \
										7, "CHOOSE WEAPONS") != 0)
		return (1);
	return (0);
}

int		init_click_opt_menu(t_editor *editor, int surf_h, int surf_w)
{
	if (create_opt_str(editor, create_vec(surf_h, surf_h * 5), \
							4, "height ceiling:") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_h, surf_h * 6), \
							5, "height floor:") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_w, surf_h * 5), \
							6, "name:") != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w * 1.2, surf_h * 5), \
							0, editor->opt_menu.file_name) != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w, surf_h * 6.5), \
							1, "SAVE MAP") != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w * 1.45, surf_h * 6.5), \
							2, "LOAD MAP") != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w, surf_h * 10), \
							3, "RETRO MUSIC") != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w, surf_h * 11.5), \
							4, "DOOM MUSIC") != 0)
		return (1);
	return (0);
}

int		init_options_menu(t_editor *editor)
{
	int surf_h;
	int surf_w;

	surf_h = editor->opt_surf->h / 20;
	surf_w = editor->opt_surf->w / 2;
	if ((editor->opt_menu.title = \
		TTF_RenderText_Solid(editor->opt_menu.font_title, \
		"Options", editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->opt_menu.title_rect, \
			create_vec((editor->opt_surf->w - editor->opt_menu.title->w) / 2, \
				editor->opt_surf->h / 30), create_vec(0, 0));
	if (init_choose_opt_menu(editor, surf_h, surf_w) != 0)
		return (1);
	if (init_click_opt_menu(editor, surf_h, surf_w) != 0)
		return (1);
	if (create_ceiling_height(editor) != 0)
		return (1);
	if (create_floor_height(editor) != 0)
		return (1);
	set_textures(editor->opt_menu.text_rect, editor->opt_surf);
	set_height(&editor->opt_menu, editor->opt_surf);
	return (0);
}
