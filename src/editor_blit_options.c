/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_blit_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:50:43 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 21:20:07 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	blit_hover_options(t_editor *editor)
{
	int i;

	i = 0;
	while (i < NBHOVEROPTIONS)
	{
		if ((SDL_BlitSurface(editor->opt_menu.hover_options[i], NULL,
			editor->opt_surf, &editor->opt_menu.hover_opt_rect[i])) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		draw_border_options(&editor->opt_menu.hover_opt_rect[i], \
					editor->opt_menu.bord_hover_color_opt[i], editor->opt_surf);
		i++;
	}
	SDL_FreeSurface(editor->opt_menu.hover_options[0]);
	editor->opt_menu.hover_options[0] = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		editor->opt_menu.file_name, editor->opt_menu.text_color);
	return (0);
}

int	blit_options(t_editor *editor)
{
	int i;

	i = 0;
	if ((SDL_BlitSurface(editor->opt_menu.title, NULL,
			editor->opt_surf, &editor->opt_menu.title_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	while (i < NBOPTIONS)
	{
		if ((SDL_BlitSurface(editor->opt_menu.options[i], NULL,
			editor->opt_surf, &editor->opt_menu.options_rect[i])) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		i++;
	}
	if (blit_hover_options(editor) != 0)
		return (1);
	return (0);
}

int	editor_blit_weapons(t_editor *editor, t_options_menu *menu)
{
	int h;

	h = editor->editor_surf->h / 20;
	assign_sdlrect(&menu->scaled_weapon_rect[0], \
			create_vec(h * 8, h * 9.5), create_vec(h * 3, h * 3));
	if (SDL_BlitScaled(editor->weapon_texture, &menu->weapon_rect[0], \
					editor->opt_surf, &menu->scaled_weapon_rect[0]) < 0)
		return (1);
	assign_sdlrect(&menu->scaled_weapon_rect[1], \
				create_vec(h * 11.5, h * 9.5), create_vec(h * 3, h * 3));
	if (SDL_BlitScaled(editor->weapon_texture, &menu->weapon_rect[1], \
					editor->opt_surf, &menu->scaled_weapon_rect[1]) < 0)
		return (1);
	draw_border_options(&menu->scaled_weapon_rect[0], \
						menu->bord_color_weapon[0], editor->opt_surf);
	draw_border_options(&menu->scaled_weapon_rect[1], \
						menu->bord_color_weapon[1], editor->opt_surf);
	return (0);
}

int	blit_height(t_editor *editor)
{
	if ((SDL_BlitSurface(editor->opt_menu.height_surf[0], \
			NULL, editor->opt_surf, &editor->opt_menu.height_rect[0])) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if ((SDL_BlitSurface(editor->opt_menu.height_surf[1], \
			NULL, editor->opt_surf, &editor->opt_menu.height_rect[1])) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	draw_border_options(&editor->opt_menu.height_rect[0], \
				editor->opt_menu.bord_color_height[0], editor->opt_surf);
	draw_border_options(&editor->opt_menu.height_rect[1], \
				editor->opt_menu.bord_color_height[1], editor->opt_surf);
	if (free_height(editor) != 0)
		return (1);
	return (0);
}

int	blit_music_and_weapon(t_editor *editor)
{
	int i;

	i = 0;
	while (i < 2)
	{
		draw_border_options(&editor->opt_menu.weapon_rect[i], \
				editor->opt_menu.bord_color_weapon[i], editor->opt_surf);
		if ((SDL_BlitScaled(editor->wall_textures[i], NULL, \
			editor->opt_surf, &editor->opt_menu.weapon_rect[i])) < 0)
			return (error_return("BlitScaled error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}
