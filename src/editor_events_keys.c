/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:33:21 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/31 15:11:51 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	key_event_u(t_editor *editor)
{
	t_wall_node	*previous;

	previous = undo_wall(editor->edit_map.sector_head);
	if (previous != NULL)
	{
		editor->wall_tmp.start.x = previous->end.x;
		editor->wall_tmp.start.y = previous->end.y;
		editor->wall_tmp.end.x = previous->end.x;
		editor->wall_tmp.end.y = previous->end.y;
	}
	else
	{
		editor->wall_tmp.start.x = -1;
		editor->wall_tmp.start.y = -1;
		editor->wall_tmp.end.x = -1;
		editor->wall_tmp.end.y = -1;
		editor->start_sector_reached = 1; // only works when there's only one sector 
	}
}

void 	key_event_t(t_editor *editor)
{
	if (editor->wall_tmp.wall_type == 1)
	{
		editor->wall_tmp.wall_type = 0;
		editor->wall_tmp.type_color = 0xFF0000;
	}
	else
	{
		editor->wall_tmp.wall_type = 1;
		editor->wall_tmp.type_color = 0xFF00FF;
	}
}

void	key_event_s(t_editor *editor)
{
	if (editor->selected_sector != NULL)
	{
		delete_sector_by_address(&editor->edit_map.sector_head, editor->selected_sector);
		editor->selected_sector = NULL;
		/*
		if (editor->selected_sector == editor->edit_map.sector_head)
			editor->edit_map.sector_head = editor->selected_sector->next;
		t_sector_node *previous_node;
		previous_node = get_previous_sector(editor->edit_map.sector_head, editor->selected_sector);
		//previous_node = editor->selected_sector->next;
		delete_sector(&editor->selected_sector);
		previous_node = editor->selected_sector;
		*/
	}
}

void 	key_event_r(t_editor *editor, t_doom *doom)
{
	if (editor->edit_map.sector_head != NULL)
		free_map(&editor->edit_map);
	//print_map_contents(&editor->edit_map);
	if (copy_map(&doom->map, &editor->edit_map) != 0)
		doom->state = QUIT_STATE;
	//editor->start_sector_reached = 1;
	//editor->edit_map.sector_head = doom->map.sector_head;
	//doom->map.sector_head = editor->edit_map.sector_head; 
	//doom->game.player.sector = doom->map.sector_head;
	//free(doom->map.sector_head);
	//doom->map.sector_head = NULL;
	//doom->map.sector_head = editor->edit_map.sector_head;

}

void 	key_event_l(t_editor *editor, t_doom *doom)
{

	if (editor->start_sector_reached == 1)
	{
		if (doom->map.sector_head != NULL)
			free_map(&doom->map);
		if (copy_map(&editor->edit_map, &doom->map) != 0)
			doom->state = QUIT_STATE;
		//can be put in game loop
		doom->game.player.pos = vec_to_vecdb(doom->map.player_spawn);
		doom->game.player.sector = get_sector_by_pos(doom->map.sector_head, doom->game.player.pos, 10);
		if (doom->game.player.pos.x == -1 && doom->game.player.pos.y == -1)
		{
			doom->game.player.sector = doom->map.sector_head;
			doom->game.player.pos = doom->map.sector_head->sector_center;
		}
		editor->loading_success = 1;
		editor->show_loading_alert = 0;
	}
	else
	{
		editor->show_loading_alert = 1;
		//editor->show_convex_alert = 0;
		//alert saying can't be loaded because sector not finished
	}
}

void event_keydown(t_editor *editor, t_doom *doom, t_sdlmain *sdlmain)
{
	check_menu(&doom->sdlmain.event, &doom->state, &doom->menu.previous_state, EDITOR_STATE);
	if (sdlmain->event.key.keysym.sym == SDLK_u && editor->start_sector_reached != 1)
	{
		key_event_u(editor);
	}
	if (sdlmain->event.key.keysym.sym == SDLK_s)
	{
		key_event_s(editor);
	}
	if (sdlmain->event.key.keysym.sym == SDLK_t && sdlmain->event.key.repeat == 0)
	{
		key_event_t(editor);
	}
	if (sdlmain->event.key.keysym.sym == SDLK_r && doom->map.sector_head != NULL)
	{
		key_event_r(editor, doom);
	}
	if (sdlmain->event.key.keysym.sym == SDLK_l && editor->edit_map.sector_head != NULL)
	{
		key_event_l(editor, doom);
	}
	if (sdlmain->event.key.keysym.sym == SDLK_p)
		give_vec_values(&editor->edit_map.player_spawn, sdlmain->mouse_pos.x, sdlmain->mouse_pos.y);
}