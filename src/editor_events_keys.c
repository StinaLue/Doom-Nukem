/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:33:21 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/04 16:23:26 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

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
		editor->start_sector_reached = 1;
	}
}

void	key_event_t(t_editor *editor)
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
		delete_sector_by_address(&editor->edit_map.sector_head, \
									editor->selected_sector);
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

void	key_event_r(t_editor *editor, t_doom *doom)
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

void	key_event_l(t_editor *editor, t_doom *doom)
{
	if (editor->start_sector_reached == 1 && get_sector_by_pos(editor->edit_map.sector_head, vec_to_vecdb(editor->edit_map.player_spawn), 10) != NULL)
	{
		if (doom->map.sector_head != NULL)
			free_map(&doom->map);
		if (copy_map(&editor->edit_map, &doom->map) != 0)
			doom->state = QUIT_STATE;
		doom->game.player.pos = vec_to_vecdb(doom->map.player_spawn);
		doom->game.player.sector = get_sector_by_pos(doom->map.sector_head, \
													doom->game.player.pos, 10);
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
	}
}

void	event_keydown(t_editor *editor, t_doom *doom, t_sdlmain *sdlmain)
{
	check_menu(&doom->sdlmain.event, &doom->state, \
				&doom->menu.previous_state, EDITOR_STATE);
	if (sdlmain->event.key.keysym.sym == SDLK_u \
					&& editor->start_sector_reached != 1)
		key_event_u(editor);
	if (sdlmain->event.key.keysym.sym == SDLK_s)
		key_event_s(editor);
	if (sdlmain->event.key.keysym.sym == SDLK_t \
					&& sdlmain->event.key.repeat == 0)
		key_event_t(editor);
	if (sdlmain->event.key.keysym.sym == SDLK_r \
					&& doom->map.sector_head != NULL)
		key_event_r(editor, doom);
	if (sdlmain->event.key.keysym.sym == SDLK_l \
					&& editor->edit_map.sector_head != NULL)
		key_event_l(editor, doom);
	/*if (sdlmain->event.key.keysym.sym == SDLK_1 && editor->opt_menu.typing_filename == 0)// editor->edit_map.sector_head != NULL)
	{
		if (editor->edit_map.sector_head == NULL)
			ft_printf("no sector in map to save\n");
		if (ft_strlen(editor->edit_map.name) <= 5)
			ft_printf("wrong map name to save\n");
		//scanf("%s", editor->edit_map.name);
		//read(0, editor->edit_map.name, 15);
		if (write_map(&editor->edit_map) != 0)
			printf("error in write map\n");
	}*/
	/*
	if (sdlmain->event.key.keysym.sym == SDLK_2)
	{
		char name[16];

		ft_bzero(name, 16);
		scanf("%s", name);
		//read(0, name, 15);
		free_map(&doom->map);
		printf("name of file is %s\n", name);
		if (read_map(name, &doom->map))
			printf("error in read map\n");
		doom->game.player.pos = vec_to_vecdb(doom->map.player_spawn);
		doom->game.player.sector = get_sector_by_pos(doom->map.sector_head, \
													doom->game.player.pos, 10);
		if (doom->game.player.pos.x == -1 && doom->game.player.pos.y == -1)
		{
			doom->game.player.sector = doom->map.sector_head;
			doom->game.player.pos = doom->map.sector_head->sector_center;
		}
	}*/
	if (sdlmain->event.key.keysym.sym == SDLK_p && editor->selected_sector != NULL)
	{
			editor->edit_map.player_spawn = vecdb_to_vec(editor->selected_sector->sector_center);
	}
	//printf("%c\n", (char)sdlmain->event.key.keysym.sym);
}
