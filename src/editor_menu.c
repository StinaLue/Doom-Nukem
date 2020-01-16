/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:43:12 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/16 13:16:32 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int create_instruct_strings(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->instruct_menu.instructions[i] = TTF_RenderText_Solid(editor->instruct_menu.font, str, editor->instruct_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->instruct_menu.instruct_rect[i], origin, create_vec(0, 0));
	return (0);
}

int create_options_strings(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->options_menu.options[i] = TTF_RenderText_Solid(editor->options_menu.font, str, editor->options_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->options_menu.options_rect[i], origin, create_vec(0, 0));
	return (0);
}

int	init_instruct_menu(t_editor *editor)
{
	if ((editor->instruct_menu.title = TTF_RenderText_Solid(editor->instruct_menu.font_title, "Instructions", editor->instruct_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->instruct_menu.title_rect, create_vec((editor->instruct_surf->w - editor->instruct_menu.title->w) / 2, (editor->instruct_surf->w - editor->instruct_menu.title->h) / 20), create_vec(0, 0));
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 18, editor->instruct_surf->w / 6), 0, "undo wall: u") != 0)
		return (1);
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 18, editor->instruct_surf->w / 4), 1, "undo sector: s") != 0)
		return (1);
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 18, editor->instruct_surf->w / 3), 2, "change type of wall: t") != 0)
		return (1);
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 2, editor->instruct_surf->w / 6), 3, "create sector: left click") != 0)
		return (1);
	if (create_instruct_strings(editor, create_vec(editor->instruct_surf->w / 2, editor->instruct_surf->w / 4), 4, "...") != 0)
		return (1);
	return (0);
}

int set_height(t_editor *editor)
{
	assign_sdlrect(&editor->options_menu.height_rect[0], create_vec((editor->options_surf->h / 20), ((editor->options_surf->h) / 20) * 7), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 26));
	assign_sdlrect(&editor->options_menu.height_rect[1], create_vec((editor->options_surf->h / 20) * 3, ((editor->options_surf->h) / 20) * 6.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 18));
	assign_sdlrect(&editor->options_menu.height_rect[2], create_vec((editor->options_surf->h / 20) * 5, ((editor->options_surf->h) / 20) * 6), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 14));
	assign_sdlrect(&editor->options_menu.height_rect[3], create_vec((editor->options_surf->h / 20) * 7, ((editor->options_surf->h) / 20) * 5.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 10));
	assign_sdlrect(&editor->options_menu.height_rect[4], create_vec((editor->options_surf->h / 20) * 3, ((editor->options_surf->h) / 20) * 7), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 26));
	assign_sdlrect(&editor->options_menu.height_rect[5], create_vec((editor->options_surf->h / 20) * 5, ((editor->options_surf->h) / 20) * 7), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 26));
	assign_sdlrect(&editor->options_menu.height_rect[6], create_vec((editor->options_surf->h / 20) * 7, ((editor->options_surf->h) / 20) * 7), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 26));
	return (0);
}

int set_textures(t_editor *editor)
{
	assign_sdlrect(&editor->options_menu.texture_rect[0], create_vec((editor->options_surf->h / 20), ((editor->options_surf->h) / 20) * 9.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[1], create_vec((editor->options_surf->h / 20), ((editor->options_surf->h) / 20) * 11.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[2], create_vec((editor->options_surf->h / 20), ((editor->options_surf->h) / 20) * 13.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[3], create_vec((editor->options_surf->h / 20) * 3, ((editor->options_surf->h) / 20) * 9.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[4], create_vec((editor->options_surf->h / 20) * 3, ((editor->options_surf->h) / 20) * 11.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[5], create_vec((editor->options_surf->h / 20) * 3, ((editor->options_surf->h) / 20) * 13.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[6], create_vec((editor->options_surf->h / 20) * 5, ((editor->options_surf->h) / 20) * 9.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[7], create_vec((editor->options_surf->h / 20) * 5, ((editor->options_surf->h) / 20) * 11.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[8], create_vec((editor->options_surf->h / 20) * 5, ((editor->options_surf->h) / 20) * 13.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[9], create_vec((editor->options_surf->h / 20) * 7, ((editor->options_surf->h) / 20) * 9.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[10], create_vec((editor->options_surf->h / 20) * 7, ((editor->options_surf->h) / 20) * 11.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	assign_sdlrect(&editor->options_menu.texture_rect[11], create_vec((editor->options_surf->h / 20) * 7, ((editor->options_surf->h) / 20) * 13.5), create_vec((editor->options_surf->w) / 16, (editor->options_surf->w) / 16));
	return (0);
}

int	init_options_menu(t_editor *editor)
{
	if ((editor->options_menu.title = TTF_RenderText_Solid(editor->options_menu.font_title, "Options", editor->options_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->options_menu.title_rect, create_vec((editor->options_surf->w - editor->options_menu.title->w) / 2, (editor->options_surf->w - editor->options_menu.title->h) / 20), create_vec(0, 0));
	if (create_options_strings(editor, create_vec((editor->options_surf->h) / 20, ((editor->options_surf->h) / 20) * 4), 0, "CHOOSE HEIGHT") != 0)
		return (1);
	if (create_options_strings(editor, create_vec((editor->options_surf->h) / 20, ((editor->options_surf->h) / 20) * 8), 1, "CHOOSE TEXTURE") != 0)
		return (1);
	if (create_options_strings(editor, create_vec((editor->options_surf->h) / 20, ((editor->options_surf->h) / 20) * 16), 2, "ENTER SOMETHING") != 0)
		return (1);
	if (create_options_strings(editor, create_vec((editor->options_surf->w) / 2, ((editor->options_surf->h) / 20) * 4), 3, "SET PLAYER POSITION") != 0)
		return (1);
	if (create_options_strings(editor, create_vec((editor->options_surf->w) / 2, ((editor->options_surf->h) / 20) * 8), 4, "CHOOSE OBJECT") != 0)
		return (1);
	if (set_textures(editor) != 0)
		return (1);
	if (set_height(editor) != 0)
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
	if ((editor->options_menu.font = TTF_OpenFont("assets/fonts/dooM.ttf", 14)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if ((editor->instruct_menu.font = TTF_OpenFont("assets/fonts/dooM.ttf",	16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	assign_sdlcolor(&editor->instruct_menu.text_color, 255, 0, 0);
	assign_sdlcolor(&editor->options_menu.text_color, 255, 0, 0);
	if (init_instruct_menu(editor) != 0)
		return (1);
	if (init_options_menu(editor) != 0)
		return (1);
	return (0);
}
