/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:43:12 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/04 14:29:32 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

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

int	create_floor_height(t_editor *editor)
{
	int i;
	const char *num;

	i = (int)editor->opt_menu.height_floor;
	if ((num = ft_itoa(i)) == NULL)
		return (1);
	if ((editor->opt_menu.floor_h_surf = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		num, editor->opt_menu.text_color)) == NULL)
		{
			ft_memdel((void **)&num);
			return (error_return("TTF_RenderText_Solid error = %s\n", \
					TTF_GetError()));
		}
	else
		ft_memdel((void **)&num);
	return (0);
}
/* 
int fill_file_name(t_editor *editor)
{
	//draw_border(editor->opt_menu.options[7], 0xff0000);
	if ((editor->opt_menu.options[7] = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		editor->opt_menu.file_name, editor->opt_menu.text_color)) == NULL)
			return (error_return("TTF_RenderText_Solid error = %s\n", \
					TTF_GetError()));
	assign_sdlrect(&editor->opt_menu.file_name_rect, create_vec((editor->instr_surf->w - editor->instr_menu.title->w) / 2, editor->instr_surf->h / 30), create_vec(0, 0));
	return (0);
} */

int	create_ceiling_height(t_editor *editor)
{
	int i;
	const char *num;

	i = (int)editor->opt_menu.height_ceiling;
	if ((num = ft_itoa(i)) == NULL)
		return (1);
	if ((editor->opt_menu.ceiling_h_surf = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		num, editor->opt_menu.text_color)) == NULL)
		{
			ft_memdel((void **)&num);
			return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		}
	else
		ft_memdel((void **)&num);
	return (0);
}

int	init_instr_menu(t_editor *editor)
{
	if ((editor->instr_menu.title = TTF_RenderText_Solid(editor->instr_menu.font_title, "Instructions", editor->instr_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->instr_menu.title_rect, create_vec((editor->instr_surf->w - editor->instr_menu.title->w) / 2, editor->instr_surf->h / 30), create_vec(0, 0));
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 18, (editor->instr_surf->h / 20) * 5), 0, "undo wall: u") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 18, (editor->instr_surf->h / 20) * 8), 1, "undo sector: s") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 18, (editor->instr_surf->h / 20) * 11), 2, "replace map: r") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 18, (editor->instr_surf->h / 20) * 14), 3, "load map: l") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 2, (editor->instr_surf->h / 20) * 5), 4, "create sector: left click") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 2, (editor->instr_surf->h / 20) * 8), 5, "create new map: n") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 2, (editor->instr_surf->h / 20) * 11), 6, "change type of wall: t") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(editor->instr_surf->w / 2, (editor->instr_surf->h / 20) * 14), 7, "set player position: p") != 0)
		return (1);
	return (0);
}

int set_height(t_editor *editor)
{
	//assign_sdlrect(&editor->opt_menu.h_rect_floor[0], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 6), create_vec((editor->opt_surf->w) / 7, (editor->opt_surf->w) / editor->opt_menu.height_floor));
	assign_sdlrect(&editor->opt_menu.h_rect_ceiling, create_vec((editor->opt_surf->h / 20) * 7, ((editor->opt_surf->h) / 20) * 5), create_vec((editor->opt_surf->w) / 7, (editor->opt_surf->w) / 11));
	//assign_sdlrect_invert(&editor->opt_menu.h_rect_ceiling[0], create_vec((editor->opt_surf->h / 20) * 3, ((editor->opt_surf->h) / 20) * 6), create_vec((editor->opt_surf->w) / 7, (editor->opt_surf->w) / editor->opt_menu.height_ceiling));
	assign_sdlrect/* _invert */(&editor->opt_menu.h_rect_floor, create_vec((editor->opt_surf->h / 20) * 7, ((editor->opt_surf->h) / 20) * 6), create_vec((editor->opt_surf->w) / 7, (editor->opt_surf->w) / 11));
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
	assign_sdlrect(&editor->opt_menu.title_rect, create_vec((editor->opt_surf->w - editor->opt_menu.title->w) / 2, editor->opt_surf->h / 30), create_vec(0, 0));
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
	if (create_opt_str(editor, create_vec((editor->opt_surf->h) / 20, ((editor->opt_surf->h) / 20) * 5), 5, "height ceiling:") != 0)
		return (1);
	if (create_opt_str(editor, create_vec((editor->opt_surf->h / 20), ((editor->opt_surf->h) / 20) * 6), 6, "height floor:") != 0)
		return (1);
	//if (ft_strlen(editor->opt_menu.file_name) != 0)
	//{
	if (create_opt_str(editor, create_vec((editor->opt_surf->h / 20), ((editor->opt_surf->h) / 20) * 17), 7, editor->opt_menu.file_name) != 0)
		return (1);
	//}
	//else
	//{
	//	if (create_opt_str(editor, create_vec((editor->opt_surf->h / 20), ((editor->opt_surf->h) / 20) * 17), 7, " ") != 0)
	//	return (1);
	//}
	
	if (create_ceiling_height(editor) != 0)
		return(1);
	if (create_floor_height(editor) != 0)
		return(1);
	//if (fill_file_name(editor) != 0)
	//	return (1);
	if (set_textures(editor) != 0)
		return (1);
	if (set_height(editor) != 0)
		return (1);
	return (0);
}

int init_fonts(t_editor *editor)
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

int	init_alerts(t_editor *editor)
{
	if ((editor->alert_convex_surf = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		"Sector has to be convex", editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->alert_convex_rect, \
			create_vec((editor->editor_surf->w - editor->alert_convex_surf->w) / 2, 0), create_vec(0, 0));
	if ((editor->alert_loading_surf = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		"Couldn't load because sector wasn't finished yet", \
			editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->alert_loading_rect, \
		create_vec((editor->editor_surf->w \
					- editor->alert_loading_surf->w) / 2, 0), create_vec(0, 0));
	if ((editor->loading_success_surf = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		"Loading map successful", editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->loading_success_rect, \
					create_vec((editor->editor_surf->w \
								- editor->loading_success_surf->w) / 2, 0), \
		create_vec(0, 0));
	return (0);
}

int	init_editor_menu(t_editor *editor)
{
	if (init_fonts(editor) != 0)
		return (1);
	if (init_instr_menu(editor) != 0)
		return (1);
	if (init_options_menu(editor) != 0)
		return (1);
	if (init_alerts(editor) != 0)
		return (1);
	return (0);
}
