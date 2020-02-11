/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init_instructs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:45:09 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 20:50:30 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_left_instr_menu(t_editor *editor, int surf_h, SDL_Surface *surf)
{
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 5), \
											0, "undo wall: u") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 8), \
												1, "undo sector: s") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 11), \
												2, "set goal: g") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 14), \
											3, "load map into game: l") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 17), \
											8, "set enemy: b/e") != 0)
		return (1);
	return (0);
}

int		init_right_instr_menu(t_editor *editor, int surf_h, SDL_Surface *surf)
{
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 5), \
										4, "choose sector: right click") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 8), \
										5, "create new map: n") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 11), \
										6, "change type of wall: t") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 14), \
										7, "set player position: p") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 17), \
										9, "remove enemy/player: r") != 0)
		return (1);
	return (0);
}

int		init_instr_menu(t_editor *editor, SDL_Surface *surf)
{
	int surf_h;

	surf_h = surf->h / 20;
	if ((editor->instr_menu.title = \
		TTF_RenderText_Solid(editor->instr_menu.font_title, \
		"Instructions", editor->instr_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->instr_menu.title_rect, \
				create_vec((surf->w - editor->instr_menu.title->w) / 2, \
							surf->h / 30), create_vec(0, 0));
	if (init_left_instr_menu(editor, surf_h, surf) != 0)
		return (1);
	if (init_right_instr_menu(editor, surf_h, surf) != 0)
		return (1);
	return (0);
}
