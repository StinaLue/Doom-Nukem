/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:43:12 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/14 16:06:15 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	init_instruct_menu(t_editor *editor)
{
	if ((editor->instruct_menu.title = TTF_RenderText_Solid(editor->instruct_menu.font, "Instructions", editor->instruct_menu.textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->instruct_menu.title_rect, create_vec((editor->instruct_surf->w - editor->instruct_menu.title->w) / 2, (editor->instruct_surf->w - editor->instruct_menu.title->h) / 20), create_vec(0, 0));
	if ((editor->instruct_menu.instructions[0] = TTF_RenderText_Solid(editor->instruct_menu.font, "undo", editor->instruct_menu.textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->instruct_menu.instruct_rect[0], create_vec((editor->instruct_surf->w - editor->instruct_menu.title->w) / 2, (editor->instruct_surf->w - editor->instruct_menu.title->h) / 20), create_vec(0, 0));
	return (0);
}

int	init_options_menu(t_editor *editor)
{
	if ((editor->options_menu.title = TTF_RenderText_Solid(editor->options_menu.font, "Options", editor->options_menu.textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->options_menu.title_rect, create_vec((editor->options_surf->w - editor->options_menu.title->w) / 2, (editor->options_surf->w - editor->options_menu.title->h) / 20), create_vec(0, 0));
	return (0);
}

int init_editor_menu(t_editor *editor)
{
	//menu->current_option = 0;
	//menu->previous_state = QUIT_STATE;
	assign_sdlcolor(&editor->options_menu.textColor, 255, 0, 0);
	if ((editor->options_menu.font = TTF_OpenFont("assets/fonts/dukes-3d.ttf", 16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	assign_sdlcolor(&editor->instruct_menu.textColor, 255, 0, 0);
	if ((editor->instruct_menu.font = TTF_OpenFont("assets/fonts/dukes-3d.ttf", 16)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if (init_instruct_menu(editor) != 0)
		return (1);
	if (init_options_menu(editor) != 0)
		return (1);
	return (0);
}
