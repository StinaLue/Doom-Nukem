/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_collide1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:05:51 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 15:26:01 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	mouse_collide_load(t_sdlmain *sdlmain, \
			t_options_menu *menu, t_editor *editor)
{
	if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[2]) \
			&& sdlmain->event.button.button == SDL_BUTTON_LEFT \
			&& editor->start_sector_reached == 1)
	{
		if (editor->selected_sector != NULL)
			remove_highlight_sector(editor->selected_sector);
		editor->selected_sector = NULL;
		free_map(&editor->edit_map);
		if (read_map(menu->file_name, &editor->edit_map) != 0)
		{
			ft_dprintf(STDERR_FILENO, "error in read map\n");
			free_map(&editor->edit_map);
		}
		else
		{
			ft_printf("%{g}s was properly loaded 😉\n", editor->edit_map.name);
			editor->opt_menu.activ_music = editor->edit_map.which_music;
			editor->opt_menu.activ_weapon = editor->edit_map.weapon_choice;
		}
	}
}

void	mouse_collide_music(t_sdlmain *sdlmain, t_options_menu *menu)
{
	if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[3]))
	{
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			menu->bord_hover_color_opt[3] = COLOR_PRESSED;
			menu->bord_hover_color_opt[4] = COLOR_NORMAL;
			menu->activ_music = 0;
		}
		else if (menu->activ_music != 0)
			menu->bord_hover_color_opt[3] = COLOR_HOVER;
	}
	if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[4]))
	{
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			menu->bord_hover_color_opt[4] = COLOR_PRESSED;
			menu->bord_hover_color_opt[3] = COLOR_NORMAL;
			menu->activ_music = 1;
		}
		else if (menu->activ_music != 1)
			menu->bord_hover_color_opt[4] = COLOR_HOVER;
	}
}

void	mouse_collide_height(t_sdlmain *sdlmain, t_editor *editor, \
								t_options_menu *menu)
{
	int i;

	i = 0;
	while (i < 2)
	{
		if (is_mouse_collide(sdlmain->mouse_pos, \
				editor->opt_menu.height_rect[i]) \
				&& editor->opt_menu.activ_height[i] != 1)
			editor->opt_menu.bord_color_height[i] = COLOR_HOVER;
		i++;
	}
	if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.height_rect[0]) \
			&& sdlmain->event.button.button == SDL_BUTTON_LEFT)
	{
		menu->activ_height[0] = 1;
		menu->activ_height[1] = 0;
		menu->bord_color_height[0] = COLOR_PRESSED;
	}
	if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.height_rect[1]) \
			&& sdlmain->event.button.button == SDL_BUTTON_LEFT)
	{
		menu->activ_height[1] = 1;
		menu->activ_height[0] = 0;
		menu->bord_color_height[1] = COLOR_PRESSED;
	}
}

void	mouse_collide1(t_sdlmain *sdlmain, t_editor *editor, \
						t_options_menu *menu)
{
	mouse_collide_music(sdlmain, menu);
	mouse_collide_load(sdlmain, menu, editor);
	mouse_collide_height(sdlmain, editor, menu);
}
