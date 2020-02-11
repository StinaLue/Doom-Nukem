/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_keys_r_to_u.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:28:00 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 11:31:59 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	key_event_r(t_editor *editor, t_doom *doom)
{
	t_vec center;

	center = vecdb_to_vec(editor->selected_sector->sector_center);
	if (center.x == editor->edit_map.player_spawn.x \
		&& center.y == editor->edit_map.player_spawn.y)
		give_vec_values(&editor->edit_map.player_spawn, -1, -1);
	else if (is_sector_occupied(editor->selected_sector, &editor->edit_map))
	{
		if ((delete_enemy_info(&editor->edit_map, center)) != 0)
		{
			ft_dprintf(STDERR_FILENO, "malloc error \
					while updating enemies info\n");
			doom->state = QUIT_STATE;
		}
	}
}

void	key_event_s(t_editor *editor)
{
	if (editor->selected_sector != NULL \
		&& !is_sector_occupied(editor->selected_sector, &editor->edit_map))
	{
		delete_sector_by_address(&editor->edit_map.sector_head, \
									editor->selected_sector);
		editor->selected_sector = NULL;
		editor->edit_map.num_sectors--;
		editor->current_sector = get_last_sector(editor->edit_map.sector_head);
	}
}

void	key_event_t(t_editor *editor)
{
	if (editor->wall_tmp.wall_type == 0)
	{
		editor->wall_tmp.wall_type = 1;
		editor->wall_tmp.type_color = 0xFF00FF;
	}
	else if (editor->wall_tmp.wall_type == 1)
	{
		editor->wall_tmp.wall_type = 2;
		editor->wall_tmp.type_color = 0x0080FF;
	}
	else if (editor->wall_tmp.wall_type == 2)
	{
		editor->wall_tmp.wall_type = 0;
		editor->wall_tmp.type_color = 0xFF0000;
	}
}

void	key_event_u(t_editor *editor)
{
	t_wall_node	*previous;

	previous = undo_wall(editor->edit_map.sector_head);
	if (previous != NULL)
	{
		editor->wall_tmp.start = previous->end;
		editor->wall_tmp.end = previous->end;
	}
	else
	{
		reset_vecdb(&editor->wall_tmp.start);
		reset_vecdb(&editor->wall_tmp.end);
		if (editor->current_sector && editor->current_sector->wall_head == NULL)
		{
			delete_sector_by_address(&editor->edit_map.sector_head, \
									editor->current_sector);
			editor->current_sector = NULL;
		}
		editor->start_sector_reached = 1;
	}
}

void	event_keydown_r_to_u(t_doom *doom, t_editor *editor, \
								SDL_Keycode key, Uint8 repeat)
{
	if (key == SDLK_r && editor->selected_sector != NULL)
		key_event_r(editor, doom);
	if (key == SDLK_s)
		key_event_s(editor);
	if (key == SDLK_t && repeat == 0)
		key_event_t(editor);
	if (key == SDLK_u && editor->start_sector_reached != 1)
		key_event_u(editor);
}
