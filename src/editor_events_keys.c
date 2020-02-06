/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:33:21 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/06 16:18:36 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int		is_sector_occupied(t_sector_node *sector, t_map *map)
{
	int i;

	i = 0;
	t_vec center;
	center = vecdb_to_vec(sector->sector_center);
	if (map->num_enemies >= 1)
	{
		while (i < map->num_enemies)
		{
			if (center.x == map->enemy_info[i].enemy_spawn.x && center.y == map->enemy_info[i].enemy_spawn.y)
				return (1);
			i++;
		}
	}
	if (center.x == map->player_spawn.x && center.y == map->player_spawn.y)
		return (1);
	return (0);
}

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
		if (editor->current_sector && editor->current_sector->wall_head == NULL)
		{
			delete_sector_by_address(&editor->edit_map.sector_head, editor->current_sector);
			editor->current_sector = NULL;
		}
		editor->start_sector_reached = 1;
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

void	key_event_s(t_editor *editor)
{
	if (editor->selected_sector != NULL && !is_sector_occupied(editor->selected_sector, &editor->edit_map))
	{
		delete_sector_by_address(&editor->edit_map.sector_head, \
									editor->selected_sector);
		editor->selected_sector = NULL;
		editor->edit_map.num_sectors--;
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

void	key_event_m(t_editor *editor, t_doom *doom)
{
	if (editor->edit_map.sector_head != NULL)
		free_map(&editor->edit_map);
	//print_map_contents(&editor->edit_map);
	if (copy_map(&doom->map, &editor->edit_map) != 0)
		doom->state = QUIT_STATE;
	editor->selected_sector = NULL;
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
	if (editor->start_sector_reached == 1 && get_sector_by_pos(editor->edit_map.sector_head, vec_to_vecdb(editor->edit_map.player_spawn)) != NULL)
	{
		if (doom->map.sector_head != NULL)
			free_map(&doom->map);
		//set_sectors_clockwise(editor->edit_map.sector_head);
		if (copy_map(&editor->edit_map, &doom->map) != 0)
			doom->state = QUIT_STATE;
		if (init_enemy_struct(&doom->game, &doom->map) != 0)
			doom->state = QUIT_STATE;
		doom->game.player.pos = vec_to_vecdb(doom->map.player_spawn);
		doom->game.player.sector = get_sector_by_pos(doom->map.sector_head, \
													doom->game.player.pos);
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

int		add_enemy_info(t_map *map, t_vec newspawn, int new_which_enem)
{
	int i;
	t_enemy_info *new_enemy_info;

	i = 0;
	if (map->num_enemies <= 0)
		return (0);
	if (map->enemy_info == NULL)
		return (1);
	if ((new_enemy_info = malloc(sizeof(t_enemy_info) * map->num_enemies)) == NULL)
	{
		ft_memdel((void **)&map->enemy_info);
		return (1);
	}
	while (i < (map->num_enemies - 1))
	{
		new_enemy_info[i] = map->enemy_info[i];
		i++;
	}
	new_enemy_info[i].enemy_spawn = newspawn;
	new_enemy_info[i].which_enemy = new_which_enem;
	ft_memdel((void **)&map->enemy_info);
	//free(map->enemy_info);
	//map->enemy_info = NULL;
	map->enemy_info = new_enemy_info;
	return (0);
}
/*
int		is_sector_occupied(t_sector_node *sector, t_map *map)
{
	int i;

	i = 0;
	t_vec center;
	center = vecdb_to_vec(sector->sector_center);
	if (map->num_enemies >= 1)
	{
		while (i < map->num_enemies)
		{
			if (center.x == map->enemy_info[i].enemy_spawn.x && center.y == map->enemy_info[i].enemy_spawn.y)
				return (1);
			i++;
		}
	}
	if (center.x == map->player_spawn.x && center.y == map->player_spawn.y)
		return (1);
	return (0);
}*/

int	delete_enemy_info(t_map *map, t_vec delspawn)
{
	int i;
	int j;
	t_enemy_info *new_enemy_info;

	i = 0;
	j = 0;
	if (map->num_enemies == 1)
	{
		ft_memdel((void **)&map->enemy_info);
		map->num_enemies--;
		return (0);
	}
	map->num_enemies--;
	if (map->enemy_info == NULL)
		return (1);
	if ((new_enemy_info = malloc(sizeof(t_enemy_info) * map->num_enemies)) == NULL)
	{
		ft_memdel((void **)&map->enemy_info);
		return (1);
	}
	while (j < map->num_enemies + 1)
	{
		if (delspawn.x == map->enemy_info[j].enemy_spawn.x && delspawn.y == map->enemy_info[j].enemy_spawn.y)
			j++;
		else
		{
			new_enemy_info[i] = map->enemy_info[j];
			i++;
			j++;
		}
	}
	ft_memdel((void **)&map->enemy_info);
	map->enemy_info = new_enemy_info;
	return (0);
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
	if (sdlmain->event.key.keysym.sym == SDLK_m \
					&& doom->map.sector_head != NULL)
		key_event_m(editor, doom);
	if (sdlmain->event.key.keysym.sym == SDLK_l \
					&& editor->edit_map.sector_head != NULL)
		key_event_l(editor, doom);
	if (sdlmain->event.key.keysym.sym == SDLK_p && editor->selected_sector != NULL)
	{
		if (is_sector_occupied(editor->selected_sector, &editor->edit_map) == 0)
			editor->edit_map.player_spawn = vecdb_to_vec(editor->selected_sector->sector_center);
	}

	if (sdlmain->event.key.keysym.sym == SDLK_e && editor->selected_sector != NULL)
	{
		if (is_sector_occupied(editor->selected_sector, &editor->edit_map) == 0)
		{
			editor->edit_map.num_enemies++;
			if (editor->edit_map.enemy_info != NULL)
			{
				if (add_enemy_info(&editor->edit_map, vecdb_to_vec(editor->selected_sector->sector_center), 0) != 0)
				{
					printf("EROORROROROROOR\n");
					doom->state = QUIT_STATE;
				}
			}
			else if (editor->edit_map.enemy_info == NULL && editor->edit_map.num_enemies == 1)
			{
				if ((editor->edit_map.enemy_info = malloc(sizeof(t_enemy_info))) == NULL)
				{
					printf("EROORROROROROOR\n");
					doom->state = QUIT_STATE;
					return ;
				}
				editor->edit_map.enemy_info[0].enemy_spawn = vecdb_to_vec(editor->selected_sector->sector_center);
				editor->edit_map.enemy_info[0].which_enemy = 0;
			}
		}
	}
	if (sdlmain->event.key.keysym.sym == SDLK_b && editor->selected_sector != NULL)
	{
		if (is_sector_occupied(editor->selected_sector, &editor->edit_map) == 0)
		{
			editor->edit_map.num_enemies++;
			if (editor->edit_map.enemy_info != NULL)
			{
				if (add_enemy_info(&editor->edit_map, vecdb_to_vec(editor->selected_sector->sector_center), 1) != 0)
				{
					printf("EROORROROROROOR\n");
					doom->state = QUIT_STATE;
				}
			}
			else if (editor->edit_map.enemy_info == NULL && editor->edit_map.num_enemies == 1)
			{
				if ((editor->edit_map.enemy_info = malloc(sizeof(t_enemy_info))) == NULL)
				{
					printf("EROORROROROROOR\n");
					doom->state = QUIT_STATE;
					return ;
				}
				editor->edit_map.enemy_info[0].enemy_spawn = vecdb_to_vec(editor->selected_sector->sector_center);
				editor->edit_map.enemy_info[0].which_enemy = 1;
			}
		}
	}
	if (sdlmain->event.key.keysym.sym == SDLK_r && editor->selected_sector != NULL)
	{
		t_vec center;

		center = vecdb_to_vec(editor->selected_sector->sector_center);
		if (center.x == editor->edit_map.player_spawn.x && center.y == editor->edit_map.player_spawn.y)
			give_vec_values(&editor->edit_map.player_spawn, -1, -1);
		else if (is_sector_occupied(editor->selected_sector, &editor->edit_map))
		{
			if ((delete_enemy_info(&editor->edit_map, center)) != 0)
			{
				printf("EROOROROEOROEROE\n");
				doom->state = QUIT_STATE;
			}
		}
	}
}
