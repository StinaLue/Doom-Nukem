/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:47:42 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/06 18:37:27 by sluetzen         ###   ########.fr       */
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

int				editor_events(t_doom *doom)
{
	t_editor	*editor;
	t_sdlmain	*sdlmain;
	SDL_Keycode key;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	key = sdlmain->event.key.keysym.sym;
	check_quit(&doom->sdlmain.event, &doom->state);
	if (sdlmain->event.type == SDL_KEYDOWN && key == SDLK_RETURN)
	{
		if (ft_strlen(editor->opt_menu.file_name) > 5)
			ft_strncpy(editor->edit_map.name, editor->opt_menu.file_name, 15);
		editor->opt_menu.typing_filename = 0;
		editor->opt_menu.bord_hover_color_opt[0] = COLOR_CHOOSE;
	}
	else if (sdlmain->event.type == SDL_KEYDOWN \
			&& (key == SDLK_DELETE || key == SDLK_BACKSPACE))
		del_last_char(editor->opt_menu.file_name, 5);
	else if (editor->opt_menu.typing_filename == 1 \
			&& sdlmain->event.type == SDL_TEXTINPUT \
			&& ft_strlen(editor->opt_menu.file_name) < 15)
		ft_strncat(editor->opt_menu.file_name, sdlmain->event.text.text, 1);
	else if (editor->opt_menu.typing_filename == 0)
	{
		if (sdlmain->event.type == SDL_KEYDOWN)
			event_keydown(editor, doom, sdlmain);
		if (sdlmain->event.type == SDL_MOUSEBUTTONDOWN \
			|| sdlmain->event.type == SDL_MOUSEMOTION \
			|| sdlmain->event.type == SDL_MOUSEWHEEL)
		{
			event_mouse(editor, sdlmain);
		}
	}
	find_neighbors(&editor->edit_map);
	itt_sector_wall_heads(editor->edit_map.sector_head, &set_wall_length);
	if (doom->state != EDITOR_STATE)
		return (1);
	return (0);
}
