/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:47:42 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 16:10:21 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void			set_wall_length(t_wall_node *head)
{
	if (head == NULL)
		return ;
	head->length = get_point_distance(head->start, head->end);
	set_wall_length(head->next);
}

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

int				editor_events(t_doom *doom, t_sdlmain *sdlmain)
{
	t_editor	*editor;
	SDL_Keycode key;
	Uint32		type;

	editor = &(doom->editor);
	key = sdlmain->event.key.keysym.sym;
	type = sdlmain->event.type;
	check_quit(&doom->sdlmain.event, &doom->state);
	event_handle_input(editor, type, key, sdlmain->event.text.text);
	if (editor->opt_menu.typing_filename == 0)
	{
		if (key == SDLK_DOWN || key == SDLK_UP || type == SDL_MOUSEWHEEL)
			key_event_height(editor, sdlmain->event, &editor->opt_menu);
		if (type == SDL_KEYDOWN)
			event_keydown(editor, doom, sdlmain);
		if (type == SDL_MOUSEBUTTONDOWN || type == SDL_MOUSEMOTION)
			event_mouse(editor, sdlmain);
	}
	doom->editor.edit_map.weapon_choice = doom->editor.opt_menu.activ_weapon;
	doom->editor.edit_map.which_music = doom->editor.opt_menu.activ_music;
	find_neighbors(&editor->edit_map);
	itt_sector_wall_heads(editor->edit_map.sector_head, &set_wall_length);
	if (doom->state != EDITOR_STATE)
		return (1);
	return (0);
}
