/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_collide2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:19:12 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 15:26:25 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	update_weapon_choice(t_sdlmain *sdlmain, \
			t_options_menu *menu, int weapon, t_vec mouse)
{
	if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
	{
		if (is_mouse_collide(mouse, menu->scaled_weapon_rect[0]))
		{
			if (weapon == 1 || weapon == 3)
				menu->bord_color_weapon[0] = COLOR_NORMAL;
			else if (weapon == 0 || weapon == 2)
				menu->bord_color_weapon[0] = COLOR_PRESSED;
			menu->activ_weapon += (weapon == 0 || weapon == 2) ? 1 : -1;
		}
		else if (is_mouse_collide(mouse, menu->scaled_weapon_rect[1]))
		{
			if (weapon == 2 || weapon == 3)
				menu->bord_color_weapon[1] = COLOR_NORMAL;
			else if (weapon == 0 || weapon == 1)
				menu->bord_color_weapon[1] = COLOR_PRESSED;
			menu->activ_weapon += (weapon == 0 || weapon == 1) ? 2 : -2;
		}
	}
	else if ((weapon == 0 || weapon == 2) \
			&& is_mouse_collide(mouse, menu->scaled_weapon_rect[0]))
		menu->bord_color_weapon[0] = COLOR_HOVER;
	else if ((weapon == 0 || weapon == 1) \
			&& is_mouse_collide(mouse, menu->scaled_weapon_rect[1]))
		menu->bord_color_weapon[1] = COLOR_HOVER;
}

void	mouse_collide_textures(t_options_menu *menu, t_vec mouse_pos, \
											Uint8 button)
{
	int i;

	i = 0;
	while (i < NBTEXTURES)
	{
		if (is_mouse_collide(mouse_pos, menu->text_rect[i]) \
							&& button == SDL_BUTTON_LEFT)
		{
			if (menu->activ_tex != i)
				menu->bord_color_text[menu->activ_tex] = COLOR_NORMAL;
			menu->bord_color_text[i] = COLOR_PRESSED;
			menu->activ_tex = i;
		}
		else
		{
			if (is_mouse_collide(mouse_pos, menu->text_rect[i]) \
								&& i != menu->activ_tex)
				menu->bord_color_text[i] = COLOR_HOVER;
			else if (!is_mouse_collide(mouse_pos, menu->text_rect[i]) \
								&& i != menu->activ_tex)
				menu->bord_color_text[i] = COLOR_NORMAL;
		}
		i++;
	}
}

void	mouse_collide_save(t_editor *editor)
{
	if (editor->selected_sector != NULL)
		remove_highlight_sector(editor->selected_sector);
	editor->selected_sector = NULL;
	if (editor->edit_map.sector_head == NULL)
	{
		ft_dprintf(STDERR_FILENO, "no sector in map to save\n");
		return ;
	}
	if (ft_strlen(editor->edit_map.name) <= 6)
	{
		ft_dprintf(STDERR_FILENO, "wrong map name to save\n");
		return ;
	}
	if (editor->edit_map.player_spawn.x == -1 \
		&& editor->edit_map.player_spawn.y == -1)
		editor->edit_map.player_spawn = \
		vecdb_to_vec(editor->edit_map.sector_head->sector_center);
	if (write_map(&editor->edit_map) != 0)
		ft_dprintf(STDERR_FILENO, "error in write map\n");
	else
		ft_printf("%{g}s was properly written 😉\n", \
				editor->edit_map.name);
}

void	mouse_collide_input(t_sdlmain *sdlmain, \
							t_options_menu *menu, Uint8 button)
{
	if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[0]) \
				&& button == SDL_BUTTON_LEFT)
	{
		menu->bord_hover_color_opt[0] = COLOR_PRESSED;
		menu->typing_filename = 1;
	}
}

void	mouse_collide2(t_sdlmain *sdlmain, t_editor *editor, \
						t_options_menu *menu, Uint8 button)
{
	int i;

	i = 0;
	sdlmain->mouse_pos.x -= editor->editor_rect.w;
	mouse_collide_textures(&editor->opt_menu, sdlmain->mouse_pos, button);
	while (i < 3)
	{
		if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[i]))
			menu->bord_hover_color_opt[i] = COLOR_HOVER;
		i++;
	}
	mouse_collide_input(sdlmain, &editor->opt_menu, button);
	if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[1]) \
		&& button == SDL_BUTTON_LEFT && editor->start_sector_reached == 1)
		mouse_collide_save(editor);
	update_weapon_choice(sdlmain, menu, menu->activ_weapon, \
						sdlmain->mouse_pos);
}
