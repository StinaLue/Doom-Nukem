/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:43:12 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/08 14:42:27 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int init_instruct_menu(t_editor *editor)
{
	if ((editor->editor_menu.title_inst = TTF_RenderText_Solid(editor->editor_menu.font, "Instructions", editor->editor_menu.textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->editor_menu.title_inst_rect, create_vec((editor->instruct_surf->w - editor->editor_menu.title_inst->w) / 2, (editor->instruct_surf->w - editor->editor_menu.title_inst->h) / 20), create_vec(0, 0));
	return (0);
}

int init_options_menu(t_editor *editor)
{
	if ((editor->editor_menu.title = TTF_RenderText_Solid(editor->editor_menu.font, "Options", editor->editor_menu.textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->editor_menu.title_rect, create_vec((editor->options_surf->w - editor->editor_menu.title->w) / 2, (editor->options_surf->w - editor->editor_menu.title->h) / 20), create_vec(0, 0));
	return (0);
}

int init_editor_menu(t_editor *editor)
{
	//menu->current_option = 0;
	//menu->previous_state = QUIT_STATE;
	assign_sdlcolor(&editor->editor_menu.textColor, 255, 0, 0);
	if ((editor->editor_menu.font = TTF_OpenFont("assets/fonts/dukes-3d.ttf", 20)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if (init_instruct_menu(editor) != 0)
		return (1);
	if (init_options_menu(editor) != 0)
		return (1);
	return (0);
}