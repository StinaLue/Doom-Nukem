/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:43:12 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/22 17:51:27 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	create_instruct_str(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->instr_menu.instructs[i] = \
		TTF_RenderText_Solid(editor->instr_menu.font, \
		str, editor->instr_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->instr_menu.instr_rect[i], origin, \
						create_vec(0, 0));
	return (0);
}

int	create_opt_str(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->opt_menu.options[i] = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		str, editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->opt_menu.options_rect[i], origin, \
					create_vec(0, 0));
	return (0);
}

int	init_instr_menu(t_editor *editor)
{
	if ((editor->instr_menu.title = TTF_RenderText_Solid(editor->instr_menu.font_title, "instructs", editor->instr_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->instr_menu.title_rect, create_vec((editor->instr_surf->w - editor->instr_menu.title->w) / 2, (editor->instr_surf->w - editor->instr_menu.title->h) / 20), create_vec(0, 0));
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 18, editor->instr_surf->w / 6), 0, "undo wall: u") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 18, editor->instr_surf->w / 4), 1, "undo sector: s") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 18, editor->instr_surf->w / 3), 2, "replace map: r") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 2, editor->instr_surf->w / 6), 3, "create sector: left click") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 2, editor->instr_surf->w / 4), 4, "create new map: n") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 2, editor->instr_surf->w / 3), 5, "change type of wall: t") != 0)
		return (1);
	return (0);
}

int set_height(t_editor *editor)
{
	assign_sdlrect(&editor->opt_menu.h_rect[0], create_vec((editor->opt_surf->h / 20), ((editor->opt_surf->h) / 20) * 7), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 26));
	assign_sdlrect(&editor->opt_menu.h_rect[1], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 6.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 18));
	assign_sdlrect(&editor->opt_menu.h_rect[2], create_vec((editor->opt_surf->h / 20) * 5, ((editor->opt_surf->h) / 20) * 6), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 14));
	assign_sdlrect(&editor->opt_menu.h_rect[3], create_vec((editor->opt_surf->h / 20) * 7, ((editor->opt_surf->h) / 20) * 5.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 10));
	assign_sdlrect(&editor->opt_menu.h_rect[4], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 7), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 26));
	assign_sdlrect(&editor->opt_menu.h_rect[5], create_vec((editor->opt_surf->h / 20) * 5, ((editor->opt_surf->h) / 20) * 7), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 26));
	assign_sdlrect(&editor->opt_menu.h_rect[6], create_vec((editor->opt_surf->h / 20) * 7, ((editor->opt_surf->h) / 20) * 7), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 26));
	return (0);
}

int set_height_test(t_editor *editor)
{
	assign_sdlrect(&editor->opt_menu.h_rect_ceiling[0], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 6), create_vec((editor->opt_surf->w) / 7, (editor->opt_surf->w) / editor->opt_menu.height_ceiling));
	assign_sdlrect(&editor->opt_menu.h_rect_ceiling[1], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 6), create_vec((editor->opt_surf->w) / 7, (editor->opt_surf->w) / 10));
	assign_sdlrect_invert(&editor->opt_menu.h_rect_floor[0], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 6), create_vec((editor->opt_surf->w) / 7, (editor->opt_surf->w) / editor->opt_menu.height_floor));
	assign_sdlrect_invert(&editor->opt_menu.h_rect_floor[1], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 6), create_vec((editor->opt_surf->w) / 7, (editor->opt_surf->w) / 12));
	return (0);
}

int set_textures(t_editor *editor)
{
	assign_sdlrect(&editor->opt_menu.text_rect[0], create_vec((editor->opt_surf->h / 20), ((editor->opt_surf->h) / 20) * 9.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	assign_sdlrect(&editor->opt_menu.text_rect[1], create_vec((editor->opt_surf->h / 20), ((editor->opt_surf->h) / 20) * 11.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	assign_sdlrect(&editor->opt_menu.text_rect[2], create_vec((editor->opt_surf->h / 20), ((editor->opt_surf->h) / 20) * 13.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	assign_sdlrect(&editor->opt_menu.text_rect[3], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 9.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	assign_sdlrect(&editor->opt_menu.text_rect[4], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 11.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	assign_sdlrect(&editor->opt_menu.text_rect[5], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 13.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	assign_sdlrect(&editor->opt_menu.text_rect[6], create_vec((editor->opt_surf->h / 20) * 5, ((editor->opt_surf->h) / 20) * 9.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	assign_sdlrect(&editor->opt_menu.text_rect[7], create_vec((editor->opt_surf->h / 20) * 5, ((editor->opt_surf->h) / 20) * 11.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	assign_sdlrect(&editor->opt_menu.text_rect[8], create_vec((editor->opt_surf->h / 20) * 5, ((editor->opt_surf->h) / 20) * 13.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	//assign_sdlrect(&editor->opt_menu.text_rect[9], create_vec((editor->opt_surf->h / 20) * 7, ((editor->opt_surf->h) / 20) * 9.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	//assign_sdlrect(&editor->opt_menu.text_rect[10], create_vec((editor->opt_surf->h / 20) * 7, ((editor->opt_surf->h) / 20) * 11.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	//assign_sdlrect(&editor->opt_menu.text_rect[11], create_vec((editor->opt_surf->h / 20) * 7, ((editor->opt_surf->h) / 20) * 13.5), create_vec((editor->opt_surf->w) / 16, (editor->opt_surf->w) / 16));
	return (0);
}

int	init_options_menu(t_editor *editor)
{
	if ((editor->opt_menu.title = TTF_RenderText_Solid(editor->opt_menu.font_title, "Options", editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->opt_menu.title_rect, create_vec((editor->opt_surf->w - editor->opt_menu.title->w) / 2, (editor->opt_surf->w - editor->opt_menu.title->h) / 20), create_vec(0, 0));
	if (create_opt_str(editor, create_vec((editor->opt_surf->h) / 20, ((editor->opt_surf->h) / 20) * 3), 0, "CHOOSE HEIGHT") != 0)
		return (1);
	if (create_opt_str(editor, create_vec((editor->opt_surf->h) / 20, ((editor->opt_surf->h) / 20) * 8.5), 1, "CHOOSE TEXTURE") != 0)
		return (1);
	if (create_opt_str(editor, create_vec((editor->opt_surf->h) / 20, ((editor->opt_surf->h) / 20) * 16), 2, "ENTER SOMETHING") != 0)
		return (1);
	if (create_opt_str(editor, create_vec((editor->opt_surf->w) / 2, ((editor->opt_surf->h) / 20) * 3), 3, "SET PLAYER POSITION") != 0)
		return (1);
	if (create_opt_str(editor, create_vec((editor->opt_surf->w) / 2, ((editor->opt_surf->h) / 20) * 8.5), 4, "CHOOSE OBJECT") != 0)
		return (1);
	if (set_textures(editor) != 0)
		return (1);
	if (set_height_test(editor) != 0)
		return (1);
	/* if (set_height(editor) != 0)
		return (1); */
	return (0);
}

int	init_editor_menu(t_editor *editor)
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
	if (init_instr_menu(editor) != 0)
		return (1);
	if (init_options_menu(editor) != 0)
		return (1);
	return (0);
}
