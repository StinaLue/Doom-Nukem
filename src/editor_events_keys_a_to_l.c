/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_keys_a_to_l.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:04:28 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 20:43:42 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	key_event_b(t_editor *editor, t_doom *doom, t_map *map)
{
	if (is_sector_occupied(editor->selected_sector, &editor->edit_map) == 0)
	{
		map->num_enemies++;
		if (map->enemy_info != NULL)
		{
			if (add_enemy_info(&editor->edit_map, \
				vecdb_to_vec(editor->selected_sector->sector_center), 1) != 0)
				doom->state = QUIT_STATE;
		}
		else if (map->enemy_info == NULL && map->num_enemies == 1)
		{
			if ((map->enemy_info = malloc(sizeof(t_enemy_info))) == NULL)
			{
				doom->state = QUIT_STATE;
				return ;
			}
			map->enemy_info[0].enemy_spawn = \
				vecdb_to_vec(editor->selected_sector->sector_center);
			map->enemy_info[0].which_enemy = 1;
		}
	}
}

void	key_event_e(t_editor *editor, t_doom *doom, t_map *map)
{
	if (is_sector_occupied(editor->selected_sector, map) == 0)
	{
		map->num_enemies++;
		if (map->enemy_info != NULL)
		{
			if (add_enemy_info(map, \
				vecdb_to_vec(editor->selected_sector->sector_center), 0) != 0)
				doom->state = QUIT_STATE;
		}
		else if (map->enemy_info == NULL && map->num_enemies == 1)
		{
			if ((map->enemy_info = \
				malloc(sizeof(t_enemy_info))) == NULL)
			{
				doom->state = QUIT_STATE;
				return ;
			}
			map->enemy_info[0].enemy_spawn = \
				vecdb_to_vec(editor->selected_sector->sector_center);
			map->enemy_info[0].which_enemy = 0;
		}
	}
}

void	key_event_g(t_editor *editor)
{
	if (editor->selected_sector->is_goal == 1)
		editor->selected_sector->is_goal = 0;
	else if (editor->selected_sector->is_goal == 0)
		editor->selected_sector->is_goal = 1;
}

void	key_event_l(t_editor *editor, t_doom *doom)
{
	if (editor->start_sector_reached == 1 \
		&& get_sector_by_pos(editor->edit_map.sector_head, \
				vec_to_vecdb(editor->edit_map.player_spawn)) != NULL)
	{
		free_enemies(&doom->game, doom->map.num_enemies);
		if (doom->map.sector_head != NULL)
			free_map(&doom->map);
		if (copy_map(&editor->edit_map, &doom->map) != 0)
			doom->state = QUIT_STATE;
		if (init_enemies(&doom->game, &doom->map) != 0)
			doom->state = QUIT_STATE;
		soft_reset_player(&doom->game.player, &doom->map);
		find_neighbors(&doom->map);
		if (doom->map.weapon_choice == 1 || doom->map.weapon_choice == 3)
			doom->game.player.current_weapon = 0;
		else if (doom->map.weapon_choice == 2)
			doom->game.player.current_weapon = 1;
		else
			doom->game.player.current_weapon = -1;
		editor->loading_success = 1;
		editor->show_loading_alert = 0;
	}
	else
		editor->show_loading_alert = 1;
}

void	event_keydown_a_to_l(t_doom *doom, t_editor *editor, SDL_Keycode key)
{
	if (key == SDLK_b && editor->selected_sector != NULL)
		key_event_b(editor, doom, &editor->edit_map);
	if (key == SDLK_e && editor->selected_sector != NULL)
		key_event_e(editor, doom, &editor->edit_map);
	if (key == SDLK_g && editor->selected_sector != NULL)
		key_event_g(editor);
	if (key == SDLK_l && editor->edit_map.sector_head != NULL)
		key_event_l(editor, doom);
}
