/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:00:02 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/04 17:13:16 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


void change_size(t_editor *editor, t_sdlmain *sdlmain)
{
	if (editor->selected_sector != NULL)
	{
		editor->opt_menu.height_floor = editor->selected_sector->floor_height;
		editor->opt_menu.height_ceiling = editor->selected_sector->ceiling_height;
		if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect_floor) && sdlmain->event.wheel.y > 0 && editor->opt_menu.height_floor > 0)
		{
			editor->opt_menu.height_floor--; // makes floor lower
			editor->selected_sector->floor_height--;
		}
		else if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect_floor) && sdlmain->event.wheel.y < 0 && editor->opt_menu.height_floor < 49 && editor->opt_menu.height_floor < editor->opt_menu.height_ceiling - 1)
		{
			editor->opt_menu.height_floor++;
			editor->selected_sector->floor_height++;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect_ceiling) && sdlmain->event.wheel.y < 0 && editor->opt_menu.height_ceiling < 50)
		{
			editor->opt_menu.height_ceiling++;
			editor->selected_sector->ceiling_height++;
		}
		else if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect_ceiling) && sdlmain->event.wheel.y > 0 && editor->opt_menu.height_ceiling > 1 && editor->opt_menu.height_floor < 49 && editor->opt_menu.height_ceiling > editor->opt_menu.height_floor + 1)
		{
			editor->opt_menu.height_ceiling--;
			editor->selected_sector->ceiling_height--;
		}
		//editor->opt_menu.height_floor = editor->selected_sector->floor_height;
		//editor->opt_menu.height_ceiling = editor->selected_sector->ceiling_height;
		set_height(editor);
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
				editor->opt_menu.bord_color_text[editor->opt_menu.activ_tex] = COLOR_NORMAL;
			editor->opt_menu.bord_color_text[i] = COLOR_PRESSED;
			editor->opt_menu.activ_tex = i;
		}
		i++;
	}
	i = 0;
	editor->opt_menu.bord_color_h = COLOR_PRESSED;
}

void mouse_in_options(t_editor *editor, t_sdlmain *sdlmain)
{
	int i;

	i = 0;
	if (is_mouse_collide(sdlmain->mouse_pos, editor->options_rect))
	{
		sdlmain->mouse_pos.x -= editor->editor_rect.w;
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			set_border_color(editor, sdlmain->mouse_pos);
			//special_case_height(editor);
		}
		while (i < NBTEXTURES)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.text_rect[i]) && i != editor->opt_menu.activ_tex)
				editor->opt_menu.bord_color_text[i] = COLOR_HOVER;
			else if (!is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.text_rect[i]) && i != editor->opt_menu.activ_tex)
				editor->opt_menu.bord_color_text[i] = COLOR_NORMAL;
			i++;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.options_rect[7]) && sdlmain->event.button.button == SDL_BUTTON_LEFT/*  && i != editor->opt_menu.activ_tex */)
		{
			//printf("is selected\n");
			editor->opt_menu.typing_filename = 1;
			//editor->opt_menu.bord_color_text[i] = COLOR_HOVER;
		}
	}
}

void	check_finished_sect(t_editor *editor)
{
	if ((editor->start_sector.x == editor->wall_tmp.end.x) \
		&& (editor->start_sector.y == editor->wall_tmp.end.y))
	{
		if (check_convex_sector(editor->current_sector) != 1)
		{
			delete_sector_by_address(&editor->edit_map.sector_head, editor->current_sector);
			editor->show_convex_alert = 1;
		}
		else
		{
			editor->show_convex_alert = 0;
			set_sector_position(editor->current_sector);
			if (check_clockwise_sector(editor->current_sector) == 0)
				flip_walls(editor->current_sector);
			editor->current_sector->floor_height = editor->opt_menu.height_floor;
			editor->current_sector->ceiling_height = editor->opt_menu.height_ceiling;
			editor->edit_map.num_sectors++;
		}
		editor->wall_tmp.start.x = -1;
		editor->wall_tmp.start.y = -1;
		editor->start_sector_reached = 1;
	}
}
int	start_wall_exists(t_wall_node *wall)
{
	if (wall->start.x > 0 && wall->start.y > 0)
		return (1);
	return (0);
}

void	event_editor_surf(t_vec mouse, t_editor *editor)
{
	if (start_wall_exists(&editor->wall_tmp) \
		&& !(mouse.x == editor->wall_tmp.end.x \
		&& mouse.y == editor->wall_tmp.end.y))
	{
		editor->wall_tmp.end.x = mouse.x;
		editor->wall_tmp.end.y = mouse.y;
		editor->wall_tmp.tex_index = editor->opt_menu.activ_tex;
		editor->current_sector = get_last_sector(editor->edit_map.sector_head);
		copy_wall_node(&editor->current_sector->wall_head, &editor->wall_tmp);
		editor->current_sector->wall_num++;
		editor->wall_tmp.start.x = editor->wall_tmp.end.x;
		editor->wall_tmp.start.y = editor->wall_tmp.end.y;
		check_finished_sect(editor);
	}
	else
	{
		if (editor->start_sector_reached == 1)
		{
			//if (editor->current_sector != NULL)
			//	set_sector_position(editor->current_sector);
			add_sector_node(&editor->edit_map.sector_head);
			set_vec_values(&mouse, &editor->start_sector);
			editor->wall_tmp.start.x = mouse.x; // set_vec_values can be used if wall_tmp.start is int
			editor->wall_tmp.start.y = mouse.y;
			editor->wall_tmp.end.x = mouse.x;
			editor->wall_tmp.end.y = mouse.y;
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

void 	mouse_click_right(t_editor *editor, t_sdlmain *sdlmain)
{
	t_sector_node *tmp_sector = editor->selected_sector;
	//selected_sector = get_sector_by_pos(editor->current_sector, vec_to_vecdb(sdlmain->mouse_pos), 10);
	//highlight_sector(selected_sector);
	editor->selected_sector = get_sector_by_pos(editor->edit_map.sector_head, vec_to_vecdb(sdlmain->mouse_pos), 10);
	if (tmp_sector != NULL && tmp_sector != editor->selected_sector)
		remove_highlight_sector(tmp_sector);
	if (tmp_sector != editor->selected_sector)
		highlight_sector(editor->selected_sector);
	//printf("%p\n", get_sector_by_pos(editor->edit_map.sector_head, vec_to_vecdb(sdlmain->mouse_pos), 5));
	// select "set_height"
	if (editor->selected_sector != NULL)
	{
		editor->opt_menu.height_floor = editor->selected_sector->floor_height;
		editor->opt_menu.height_ceiling = editor->selected_sector->ceiling_height;
	}
	//printf("sel sec: %p\n", editor->selected_sector);
	set_height(editor);
	//check_convex_sector(editor->edit_map.sector_head);
}

void event_mouse(t_editor *editor, t_sdlmain *sdlmain)
{
	if (sdlmain->event.button.button == SDL_BUTTON_LEFT && sdlmain->mouse_pos.x <= NBPOINTSROW && sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
		event_editor_surf(sdlmain->mouse_pos, editor);
	if (sdlmain->event.button.button == SDL_BUTTON_RIGHT && sdlmain->mouse_pos.x <= NBPOINTSROW && sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
	{
		mouse_click_right(editor, sdlmain);
	}
	SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
	mouse_in_options(editor, sdlmain);
	if (sdlmain->event.type == SDL_MOUSEWHEEL)
		change_size(editor, sdlmain);
}