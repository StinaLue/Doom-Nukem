/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:00:02 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/07 00:47:24 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	change_size(t_editor *editor, t_sdlmain *sdlmain, t_options_menu *menu)
{
	if (editor->selected_sector != NULL)
	{
		menu->height_floor = editor->selected_sector->floor_height;
		menu->height_ceiling = editor->selected_sector->ceiling_height;
		if (is_mouse_collide(sdlmain->mouse_pos, menu->height_rect[1]) \
			&& sdlmain->event.wheel.y > 0 && menu->height_floor > 0)
		{
			menu->height_floor--;
			editor->selected_sector->floor_height--;
		}
		else if (is_mouse_collide(sdlmain->mouse_pos, menu->height_rect[1]) \
				&& sdlmain->event.wheel.y < 0 && menu->height_floor < 49 \
				&& menu->height_floor < menu->height_ceiling - 1)
		{
			menu->height_floor++;
			editor->selected_sector->floor_height++;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, menu->height_rect[0]) \
				&& sdlmain->event.wheel.y < 0 && menu->height_ceiling < 50)
		{
			menu->height_ceiling++;
			editor->selected_sector->ceiling_height++;
		}
		else if (is_mouse_collide(sdlmain->mouse_pos, menu->height_rect[0]) \
				&& sdlmain->event.wheel.y > 0 && menu->height_ceiling > 1 \
				&& menu->height_floor < 49 \
				&& menu->height_ceiling > menu->height_floor + 1)
		{
			menu->height_ceiling--;
			editor->selected_sector->ceiling_height--;
		}
		set_height(&editor->opt_menu, editor->opt_surf);
	}
}

void	set_border_color(t_editor *editor, t_vec mouse_pos)
{
	int i;

	i = 0;
	while (i < NBTEXTURES)
	{
		if (is_mouse_collide(mouse_pos, editor->opt_menu.text_rect[i]))
		{
			if (editor->opt_menu.activ_tex != i)
				editor->opt_menu.bord_color_text\
				[editor->opt_menu.activ_tex] = COLOR_NORMAL;
			editor->opt_menu.bord_color_text[i] = COLOR_PRESSED;
			editor->opt_menu.activ_tex = i;
		}
		i++;
	}
}

void	mouse_in_options(t_editor *editor, t_sdlmain *sdlmain, \
							t_options_menu *menu, t_doom *doom)
{
	int i;

	i = 0;
	if (is_mouse_collide(sdlmain->mouse_pos, editor->options_rect))
	{
		sdlmain->mouse_pos.x -= editor->editor_rect.w;
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			set_border_color(editor, sdlmain->mouse_pos);
		}
		while (i < NBTEXTURES)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, menu->text_rect[i]) \
								&& i != menu->activ_tex)
				menu->bord_color_text[i] = COLOR_HOVER;
			else if (!is_mouse_collide(sdlmain->mouse_pos, menu->text_rect[i]) \
								&& i != menu->activ_tex)
				menu->bord_color_text[i] = COLOR_NORMAL;
			i++;
		}
		i = 0;
		while (i < 2)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, menu->height_rect[i]))
				menu->bord_color_opt[i] = COLOR_PRESSED;
			i++;
		}
		i = 0;
		while (i < NBHOVEROPTIONS)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[i]))
			{
				if (i != 3 && i != 4)
					menu->bord_hover_color_opt[i] = COLOR_HOVER;
				else if (i == 3 && menu->activ_music[0] == 0)
					menu->bord_hover_color_opt[i] = COLOR_HOVER;
				else if (i == 4 && menu->activ_music[1] == 0)
					menu->bord_hover_color_opt[i] = COLOR_HOVER;
			}
			i++;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[0]) \
					&& sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			menu->bord_hover_color_opt[0] = COLOR_PRESSED;
			menu->typing_filename = 1;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[1]) \
				&& sdlmain->event.button.button == SDL_BUTTON_LEFT && editor->start_sector_reached == 1)
		{
			if (editor->selected_sector != NULL)
				remove_highlight_sector(editor->selected_sector);
			editor->selected_sector = NULL;
			if (editor->edit_map.sector_head == NULL)
			{
				ft_dprintf(STDERR_FILENO, "no sector in map to save\n");
				return ;
			}
			if (ft_strlen(editor->edit_map.name) <= 6)
			{
				ft_dprintf(STDERR_FILENO, "wrong map name to save\n");
				return ;
			}
			if (editor->edit_map.player_spawn.x == -1 \
				&& editor->edit_map.player_spawn.y == -1)
				editor->edit_map.player_spawn = \
				vecdb_to_vec(editor->edit_map.sector_head->sector_center);
			if (write_map(&editor->edit_map) != 0)
			{
				ft_dprintf(STDERR_FILENO, "error in write map\n"); //THIS IS NOT SECURE YET
				doom->state = QUIT_STATE;
			}
			ft_printf("%{g}s was properly written 😉\n", editor->edit_map.name);
		}
		if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[3]) \
				&& sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			menu->bord_hover_color_opt[3] = COLOR_PRESSED;
			menu->bord_hover_color_opt[4] = COLOR_CHOOSE;
			menu->activ_music[0] = 1;
			menu->activ_music[1] = 0;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[4]) \
				&& sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			menu->bord_hover_color_opt[4] = COLOR_PRESSED;
			menu->bord_hover_color_opt[3] = COLOR_CHOOSE;
			menu->activ_music[0] = 0;
			menu->activ_music[1] = 1;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, menu->weapon_rect[0]) \
				&& sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			if (menu->bord_color_weapon[0] == COLOR_PRESSED)
				menu->bord_color_weapon[0] = COLOR_CHOOSE;
			else
				menu->bord_color_weapon[0] = COLOR_PRESSED;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, menu->weapon_rect[1]) \
				&& sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			if (menu->bord_color_weapon[1] == COLOR_PRESSED)
				menu->bord_color_weapon[1] = COLOR_CHOOSE;
			else
				menu->bord_color_weapon[1] = COLOR_PRESSED;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[2]) \
				&& sdlmain->event.button.button == SDL_BUTTON_LEFT && editor->start_sector_reached == 1)
		{
			if (editor->selected_sector != NULL)
				remove_highlight_sector(editor->selected_sector);
			editor->selected_sector = NULL;
			free_map(&editor->edit_map);
			if (read_map(menu->file_name, &editor->edit_map))
			{
				ft_dprintf(STDERR_FILENO, "error in read map\n");
				doom->state = QUIT_STATE;
			}
			ft_printf("%{g}s was properly loaded 😉\n", editor->edit_map.name);
		}
	}
}

void	check_finished_sect(t_editor *editor, t_sector_node *sector)
{
	if ((editor->start_sector.x == editor->wall_tmp.end.x) \
		&& (editor->start_sector.y == editor->wall_tmp.end.y))
	{
		if (check_convex_sector(sector) != 1)
		{
			delete_sector_by_address(&editor->edit_map.sector_head, sector);
			sector = NULL;
			editor->show_convex_alert = 1;
		}
		else
		{
			editor->show_convex_alert = 0;
			set_sector_position(sector);
			if (check_clockwise_sector(sector) == 0)
				flip_walls(sector);
			sector->floor_height = editor->opt_menu.height_floor;
			sector->ceiling_height = editor->opt_menu.height_ceiling;
			editor->edit_map.num_sectors++;
		}
		editor->wall_tmp.start.x = -1;
		editor->wall_tmp.start.y = -1;
		editor->start_sector_reached = 1;
	}
}

int		start_wall_exists(t_wall_node *wall)
{
	if (wall->start.x > 0 && wall->start.y > 0)
		return (1);
	return (0);
}

void	event_editor_surf(t_vec mouse, t_editor *editor, t_wall_node *wall)
{
	if (start_wall_exists(wall) && !(mouse.x == wall->end.x \
				&& mouse.y == wall->end.y))
	{
		wall->end.x = mouse.x * MAPMULTIPLIER; // assign vector multiplied
		wall->end.y = mouse.y * MAPMULTIPLIER;
		wall->tex_index = editor->opt_menu.activ_tex;
		editor->current_sector = get_last_sector(editor->edit_map.sector_head);
		copy_wall_node(&editor->current_sector->wall_head, wall);
		editor->current_sector->wall_num++;
		wall->start.x = wall->end.x;
		wall->start.y = wall->end.y;
		check_finished_sect(editor, editor->current_sector);
	}
	else
	{
		if (editor->start_sector_reached == 1)
		{
			add_sector_node(&editor->edit_map.sector_head);
			editor->start_sector.x = mouse.x * MAPMULTIPLIER;
			editor->start_sector.y = mouse.y * MAPMULTIPLIER;
			wall->start.x = mouse.x * MAPMULTIPLIER;
			wall->start.y = mouse.y * MAPMULTIPLIER;
			wall->end.x = mouse.x * MAPMULTIPLIER;
			wall->end.y = mouse.y * MAPMULTIPLIER;
			editor->start_sector_reached = 0;
		}
	}
}

void	highlight_sector(t_sector_node *selected_sector)
{
	t_wall_node *current_wall;

	if (selected_sector == NULL)
		return ;
	current_wall = selected_sector->wall_head;
	while (current_wall != NULL)
	{
		current_wall->color = current_wall->type_color;
		current_wall->type_color = 0xFFFFFF;
		current_wall = current_wall->next;
	}
}

void	remove_highlight_sector(t_sector_node *sector)
{
	t_wall_node *current_wall;

	if (sector == NULL)
		return ;
	current_wall = sector->wall_head;
	while (current_wall != NULL)
	{
		current_wall->type_color = current_wall->color;
		current_wall->color = 0xFFFFFF;
		current_wall = current_wall->next;
	}
}

void	mouse_click_right(t_editor *editor, t_sdlmain *sdlmain)
{
	t_sector_node	*tmp_sector;
	t_vec			tmp_mouse;

	tmp_mouse = sdlmain->mouse_pos;
	tmp_sector = editor->selected_sector;
	tmp_mouse.x = tmp_mouse.x * MAPMULTIPLIER;
	tmp_mouse.y = tmp_mouse.y * MAPMULTIPLIER; //assign vector multiplied
	if (editor->start_sector_reached == 1)
		editor->selected_sector = \
		get_sector_by_pos(editor->edit_map.sector_head, \
							vec_to_vecdb(tmp_mouse));
	if (tmp_sector != NULL && tmp_sector != editor->selected_sector)
		remove_highlight_sector(tmp_sector);
	if (tmp_sector != editor->selected_sector)
		highlight_sector(editor->selected_sector);
	if (editor->selected_sector != NULL)
	{
		editor->opt_menu.height_floor = editor->selected_sector->floor_height;
		editor->opt_menu.height_ceiling = \
			editor->selected_sector->ceiling_height;
	}
	set_height(&editor->opt_menu, editor->opt_surf);
}

void	event_mouse(t_editor *editor, t_doom *doom, t_sdlmain *sdlmain)
{
	if (sdlmain->event.button.button == SDL_BUTTON_LEFT \
		&& sdlmain->mouse_pos.x <= NBPOINTSROW \
		&& sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
		event_editor_surf(sdlmain->mouse_pos, editor, &editor->wall_tmp);
	if (sdlmain->event.button.button == SDL_BUTTON_RIGHT \
		&& sdlmain->mouse_pos.x <= NBPOINTSROW \
		&& sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
	{
		mouse_click_right(editor, sdlmain);
	}
	editor->opt_menu.bord_color_opt[0] = COLOR_CHOOSE; // move somewhere else
	editor->opt_menu.bord_color_opt[1] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[0] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[1] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[2] = COLOR_CHOOSE;
	if (editor->opt_menu.activ_music[0] != 1)
		editor->opt_menu.bord_hover_color_opt[3] = COLOR_CHOOSE;
	if (editor->opt_menu.activ_music[1] != 1)
		editor->opt_menu.bord_hover_color_opt[4] = COLOR_CHOOSE;
	SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
	mouse_in_options(editor, sdlmain, &editor->opt_menu, doom);
	if (sdlmain->event.type == SDL_MOUSEWHEEL)
		change_size(editor, sdlmain, &editor->opt_menu);
}
