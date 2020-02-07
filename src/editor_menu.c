/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:43:12 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/07 12:25:12 by sluetzen         ###   ########.fr       */
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

int	create_hover_opt(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->opt_menu.hover_options[i] = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		str, editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->opt_menu.hover_opt_rect[i], origin, \
					create_vec(0, 0));
	return (0);
}

int	create_floor_height(t_editor *editor)
{
	int			i;
	const char	*num;

	i = (int)editor->opt_menu.height_floor;
	if ((num = ft_itoa(i)) == NULL)
		return (1);
	if ((editor->opt_menu.height_surf[1] = \
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

int	create_ceiling_height(t_editor *editor)
{
	int			i;
	const char	*num;

	i = (int)editor->opt_menu.height_ceiling;
	if ((num = ft_itoa(i)) == NULL)
		return (1);
	if ((editor->opt_menu.height_surf[0] = \
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

int	init_instr_menu(t_editor *editor, SDL_Surface *surf)
{
	int surf_h;

	surf_h = surf->h / 20;
	if ((editor->instr_menu.title = TTF_RenderText_Solid(editor->instr_menu.font_title, "Instructions", editor->instr_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->instr_menu.title_rect, create_vec((surf->w - editor->instr_menu.title->w) / 2, surf->h / 30), create_vec(0, 0));
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 5), 0, "undo wall: u") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 8), 1, "undo sector: s") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 11), 2, "replace map: m") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 14), 3, "load map into game: l") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 5), 4, "choose sector: right click") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 8), 5, "create new map: n") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 11), 6, "change type of wall: t") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 14), 7, "set player position: p") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 18, surf_h * 17), 8, "set enemy: b/e") != 0)
		return (1);
	if (create_instruct_str(editor, create_vec(surf->w / 2, surf_h * 17), 9, "remove enemy/player: r") != 0)
		return (1);
	return (0);
}

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
	//assign_sdlrect(&menu->text_rect[9], create_vec((h) * 7, (h) * 10), create_vec(w, w));
	//assign_sdlrect(&menu->text_rect[10], create_vec((h) * 7, (h) * 12), create_vec(w, w));
	//assign_sdlrect(&menu->text_rect[11], create_vec((h) * 7, (h) * 14), create_vec(w, w));
}

void	set_weapon_textures(t_options_menu *menu, SDL_Surface *surf)
{
	int height;
	int width;

	height = surf->h / 20;
	width = surf->w / 16;
	assign_sdlrect(&menu->weapon_rect[0], \
				create_vec(height * 12, height * 14), create_vec(width, width));
	assign_sdlrect(&menu->weapon_rect[1], \
				create_vec(height * 15, height * 14), create_vec(width, width));
}

int	init_options_menu(t_editor *editor)
{
	int surf_h;
	int surf_w;

	surf_h = editor->opt_surf->h / 20;
	surf_w = editor->opt_surf->w / 2;
	if ((editor->opt_menu.title = TTF_RenderText_Solid(editor->opt_menu.font_title, "Options", editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	assign_sdlrect(&editor->opt_menu.title_rect, create_vec((editor->opt_surf->w - editor->opt_menu.title->w) / 2, editor->opt_surf->h / 30), create_vec(0, 0));
	if (create_opt_str(editor, create_vec(surf_h, surf_h * 3), 0, "CHOOSE HEIGHT") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_h, surf_h * 8.5), 1, "CHOOSE TEXTURE") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_w, surf_h * 3), 2, "LOAD/SAVE MAP") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_w, surf_h * 8.5), 3, "CHOOSE MUSIC") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_h, surf_h * 5), 4, "height ceiling:") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_h, surf_h * 6), 5, "height floor:") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_w, surf_h * 5), 6, "name:") != 0)
		return (1);
	if (create_opt_str(editor, create_vec(surf_w, surf_h * 13), 7, "CHOOSE WEAPONS") != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w * 1.2, surf_h * 5), 0, editor->opt_menu.file_name) != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w, surf_h * 6.5), 1, "SAVE MAP") != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w * 1.45, surf_h * 6.5), 2, "LOAD MAP") != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w, surf_h * 10), 3, "RETRO MUSIC") != 0)
		return (1);
	if (create_hover_opt(editor, create_vec(surf_w, surf_h * 11.5), 4, "DOOM MUSIC") != 0)
		return (1);
	if (create_ceiling_height(editor) != 0)
		return (1);
	if (create_floor_height(editor) != 0)
		return (1);
	set_textures(editor->opt_menu.text_rect, editor->opt_surf);
	set_weapon_textures(&editor->opt_menu, editor->opt_surf);
	set_height(&editor->opt_menu, editor->opt_surf);
	return (0);
}

int	init_fonts(t_editor *editor)
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

int	init_alerts(t_editor *editor, SDL_Surface *surf)
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
		"Couldn't load because sector wasn't finished yet", \
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
