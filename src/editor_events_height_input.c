/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_height_input.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:54:15 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/10 16:56:46 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void			del_last_char(char *str, int min_len)
{
	int len;

	if (str == NULL)
		return ;
	len = ft_strlen(str);
	if (len > (min_len + 1))
		str[len - 1] = '\0';
}

void			height_down(t_editor *editor, t_options_menu *menu)
{
	if (menu->activ_height[1] == 1 && menu->height_floor > 0)
	{
		menu->height_floor--;
		editor->selected_sector->floor_height--;
	}
	else if (menu->activ_height[0] == 1 && menu->height_ceiling > 1 \
			&& menu->height_floor < 99 \
			&& menu->height_ceiling > menu->height_floor + 1)
	{
		menu->height_ceiling--;
		editor->selected_sector->ceiling_height--;
	}
}

void			height_up(t_editor *editor, t_options_menu *menu)
{
	if (menu->activ_height[1] == 1 && menu->height_floor < 99 \
			&& menu->height_floor < menu->height_ceiling - 1)
	{
		menu->height_floor++;
		editor->selected_sector->floor_height++;
	}
	else if (menu->activ_height[0] == 1 && menu->height_ceiling < 100)
	{
		menu->height_ceiling++;
		editor->selected_sector->ceiling_height++;
	}
}

void			key_event_height(t_editor *editor, SDL_Event ev, \
										t_options_menu *menu)
{
	if (editor->selected_sector != NULL)
	{
		menu->height_floor = editor->selected_sector->floor_height;
		menu->height_ceiling = editor->selected_sector->ceiling_height;
		if (ev.key.keysym.sym == SDLK_DOWN \
			|| (ev.type == SDL_MOUSEWHEEL && ev.wheel.y > 0))
			height_down(editor, menu);
		else if (ev.key.keysym.sym == SDLK_UP \
			|| (ev.type == SDL_MOUSEWHEEL && ev.wheel.y < 0))
			height_up(editor, menu);
		set_height(&editor->opt_menu, editor->opt_surf);
	}
}

void			event_handle_input(t_editor *editor, Uint32 type, \
							SDL_Keycode key, char *text)
{
	if (type == SDL_KEYDOWN && key == SDLK_RETURN)
	{
		if (ft_strlen(editor->opt_menu.file_name) > 5)
			ft_strncpy(editor->edit_map.name, editor->opt_menu.file_name, 15);
		editor->opt_menu.typing_filename = 0;
		editor->opt_menu.bord_hover_color_opt[0] = COLOR_CHOOSE;
	}
	if (type == SDL_KEYDOWN && (key == SDLK_DELETE || key == SDLK_BACKSPACE))
		del_last_char(editor->opt_menu.file_name, 5);
	else if (editor->opt_menu.typing_filename == 1 && type == SDL_TEXTINPUT \
			&& ft_strlen(editor->opt_menu.file_name) < 15)
		ft_strncat(editor->opt_menu.file_name, text, 1);
}
