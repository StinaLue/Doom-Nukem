/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_keys_m_to_q.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:22:02 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/12 11:28:43 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	key_event_m(t_editor *editor, t_doom *doom)
{
	if (editor->edit_map.sector_head != NULL)
		free_map(&editor->edit_map);
	editor->start_sector_reached = 1;
	reset_vec(&editor->edit_map.player_spawn);
	editor->edit_map.sector_head = NULL;
	editor->current_sector = NULL;
	editor->current_wall = NULL;
	reset_vecdb(&editor->wall_tmp.start);
	reset_vecdb(&editor->wall_tmp.end);
	if (copy_map(&doom->map, &editor->edit_map) != 0)
		doom->state = QUIT_STATE;
	editor->selected_sector = NULL;
}

void	key_event_n(t_editor *editor)
{
	free_map(&editor->edit_map);
	editor->start_sector_reached = 1;
	reset_vec(&editor->edit_map.player_spawn);
	editor->edit_map.sector_head = NULL;
	editor->current_sector = NULL;
	editor->current_wall = NULL;
	editor->selected_sector = NULL;
	reset_vecdb(&editor->wall_tmp.start);
	reset_vecdb(&editor->wall_tmp.end);
}

void	key_event_p(t_editor *editor)
{
	if (is_sector_occupied(editor->selected_sector, &editor->edit_map) == 0)
		editor->edit_map.player_spawn = \
			vecdb_to_vec(editor->selected_sector->sector_center);
}

void	event_keydown_m_to_q(t_doom *doom, t_editor *editor, SDL_Keycode key)
{
	if (key == SDLK_m && doom->map.sector_head != NULL)
		key_event_m(editor, doom);
	if (key == SDLK_n)
		key_event_n(editor);
	if (key == SDLK_p && editor->selected_sector != NULL)
		key_event_p(editor);
}
