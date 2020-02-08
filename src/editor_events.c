/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:47:42 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/08 02:44:59 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int				compare_walls(t_wall_node *current_wall, t_wall_node *wall)
{
	if (current_wall->start.x == wall->end.x \
		&& current_wall->start.y == wall->end.y \
		&& current_wall->end.x == wall->start.x \
		&& current_wall->end.y == wall->start.y)
	{
		return (1);
	}
	return (0);
}

t_sector_node	*find_wall_neighbor(t_wall_node *wall, \
										t_sector_node *sector_list)
{
	t_sector_node	*current_sector;
	t_wall_node		*current_wall;

	current_sector = sector_list;
	while (current_sector != NULL)
	{
		current_wall = current_sector->wall_head;
		while (current_wall != NULL)
		{
			if (compare_walls(current_wall, wall) == 1)
				return (current_sector);
			current_wall = current_wall->next;
		}
		current_sector = current_sector->next;
	}
	return (NULL);
}

void			find_neighbors(t_map *map)
{
	t_sector_node	*current_sector;
	t_wall_node		*current_wall;

	current_sector = map->sector_head;
	while (current_sector != NULL)
	{
		current_wall = current_sector->wall_head;
		while (current_wall != NULL)
		{
			if (current_wall->wall_type == 1 || current_wall->wall_type == 2)
				current_wall->neighbor_sector = \
						find_wall_neighbor(current_wall, map->sector_head);
			else
				current_wall->neighbor_sector = NULL;
			current_wall = current_wall->next;
		}
		current_sector = current_sector->next;
	}
}

void			del_last_char(char *str, int min_len)
{
	int len;

	if (str == NULL)
		return ;
	len = ft_strlen(str);
	if (len > (min_len + 1))
		str[len - 1] = '\0';
}

void	height_down(t_editor *editor, t_options_menu *menu)
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

void	height_up(t_editor *editor, t_options_menu *menu)
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

void	key_event_height(t_editor *editor, SDL_Event ev, t_options_menu *menu)
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

void	event_handle_input(t_editor *editor, Uint32 type, SDL_Keycode key, char *text)
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

int				editor_events(t_doom *doom)
{
	t_editor	*editor;
	t_sdlmain	*sdlmain;
	SDL_Keycode key;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	key = sdlmain->event.key.keysym.sym;
	check_quit(&doom->sdlmain.event, &doom->state);
	event_handle_input(editor, sdlmain->event.type, key, sdlmain->event.text.text);
	if (editor->opt_menu.typing_filename == 0)
	{
		if (sdlmain->event.type == SDL_KEYDOWN)
			event_keydown(editor, doom, sdlmain);
		if (sdlmain->event.type == SDL_MOUSEBUTTONDOWN || sdlmain->event.type == SDL_MOUSEMOTION \
				|| sdlmain->event.type == SDL_MOUSEWHEEL)
			event_mouse(editor, sdlmain);
		if (key == SDLK_DOWN || key == SDLK_UP || sdlmain->event.type == SDL_MOUSEWHEEL)
			key_event_height(editor, sdlmain->event, &editor->opt_menu);
	}
	doom->editor.edit_map.weapon_choice = doom->editor.opt_menu.activ_weapon;
	doom->editor.edit_map.which_music = doom->editor.opt_menu.activ_music;
	find_neighbors(&editor->edit_map);
	itt_sector_wall_heads(editor->edit_map.sector_head, &set_wall_length);
	if (doom->state != EDITOR_STATE)
		return (1);
	return (0);
}
