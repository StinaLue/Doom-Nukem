/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:43:12 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/15 11:44:15 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int create_instruct_strings(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->instruct_menu.instructions[i] = TTF_RenderText_Solid(editor->instruct_menu.font, str, editor->instruct_menu.textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->instruct_menu.instruct_rect[i], origin, create_vec(0, 0));
	return (0);
}

int create_options_strings(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->options_menu.options[i] = TTF_RenderText_Solid(editor->options_menu.font, str, editor->options_menu.textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->options_menu.options_rect[i], origin, create_vec(0, 0));
	return (0);
}

int	init_instruct_menu(t_editor *editor)
{
	if ((editor->instruct_menu.title = TTF_RenderText_Solid(editor->instruct_menu.font_title, "Instructions", editor->instruct_menu.textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->instruct_menu.title_rect, create_vec((editor->instruct_surf->w - editor->instruct_menu.title->w) / 2, (editor->instruct_surf->w - editor->instruct_menu.title->h) / 20), create_vec(0, 0));
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 18, (editor->instruct_surf->w) / 6), 0, "undo wall: u") != 0)
		return (1);
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 18, (editor->instruct_surf->w) / 4), 1, "undo sector: s") != 0)
		return (1);
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 18, (editor->instruct_surf->w) / 3), 2, "change type of wall: t") != 0)
		return (1);
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 2, (editor->instruct_surf->w) / 6), 3, "create sector: left click") != 0)
		return (1);
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 2, (editor->instruct_surf->w) / 4), 4, "...") != 0)
		return (1);
	return (0);
}

int	init_options_menu(t_editor *editor)
{
	if ((editor->options_menu.title = TTF_RenderText_Solid(editor->options_menu.font_title, "Options", editor->options_menu.textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->options_menu.title_rect, create_vec((editor->options_surf->w - editor->options_menu.title->w) / 2, (editor->options_surf->w - editor->options_menu.title->h) / 20), create_vec(0, 0));
	if (create_options_strings(editor, create_vec((editor->options_surf->w) / 18, (editor->options_surf->w) / 6), 0, "..........") != 0)
		return (1);
	if (create_options_strings(editor, create_vec((editor->options_surf->w) / 18, (editor->options_surf->w) / 4), 1, "..........") != 0)
		return (1);
	if (create_options_strings(editor, create_vec((editor->options_surf->w) / 18, (editor->options_surf->w) / 3), 2, "..........") != 0)
		return (1);
	if (create_options_strings(editor, create_vec((editor->options_surf->w) / 2, (editor->options_surf->w) / 6), 3, "...........") != 0)
		return (1);
	return (0);
}

int init_editor_menu(t_editor *editor)
{
	//menu->current_option = 0;
	//menu->previous_state = QUIT_STATE;
	if ((editor->options_menu.font_title = TTF_OpenFont("assets/fonts/dukes-3d.ttf", 16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if ((editor->instruct_menu.font_title = TTF_OpenFont("assets/fonts/dukes-3d.ttf", 16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if ((editor->options_menu.font = TTF_OpenFont("assets/fonts/dooM.ttf", 16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if ((editor->instruct_menu.font = TTF_OpenFont("assets/fonts/dooM.ttf",	16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	assign_sdlcolor(&editor->instruct_menu.textColor, 255, 0, 0);
	assign_sdlcolor(&editor->options_menu.textColor, 255, 0, 0);
	if (init_instruct_menu(editor) != 0)
		return (1);
	if (init_options_menu(editor) != 0)
		return (1);
	return (0);
}
