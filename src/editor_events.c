/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:47:42 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/22 17:46:25 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_finished_sect(t_editor *editor)
{
	if ((editor->start_sector.x == editor->wall_tmp.end.x) \
		&& (editor->start_sector.y == editor->wall_tmp.end.y))
	{
		editor->clicked = 0;
		editor->start_sector_reached = 1;
		editor->num_sectors++;
		editor->wall_tmp.start.x = -1;
		editor->wall_tmp.start.y = -1;
		set_sector_position(editor->current_sector);
	}
}

int	start_wall_exists(t_wall_node *wall)
{
	if (wall->start.x > 0 && wall->start.y > 0)
		return (1);
	return (0);
}

/* int is_convex()
{
	return(1);
} */

void	event_editor_surf(t_vec mouse, t_editor *editor)
{
	if (start_wall_exists(&editor->wall_tmp) \
		&& !(mouse.x == editor->wall_tmp.end.x \
		&& mouse.y == editor->wall_tmp.end.y))
	{
		/* if (is_convex())
			printf("is convex\n");
		else
			printf("is not convex\n"); */
		editor->wall_tmp.end.x = mouse.x;
		editor->wall_tmp.end.y = mouse.y;
		editor->wall_tmp.tex_index = editor->opt_menu.activ_tex;
		editor->current_sector = get_last_sector(editor->edit_map.sector_head);
		copy_wall_node(&editor->current_sector->wall_head, &editor->wall_tmp);
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

void	special_case_height(t_editor *editor)
{
	if (editor->opt_menu.activ_h == 1 \
		|| editor->opt_menu.activ_h == 4)
	{
		editor->opt_menu.bord_color_h[1] = COLOR_PRESSED;
		editor->opt_menu.bord_color_h[4] = COLOR_PRESSED;
		editor->opt_menu.activ_h = 1;
	}
	if (editor->opt_menu.activ_h == 2 \
		|| editor->opt_menu.activ_h == 5)
	{
		editor->opt_menu.bord_color_h[2] = COLOR_PRESSED;
		editor->opt_menu.bord_color_h[5] = COLOR_PRESSED;
		editor->opt_menu.activ_h = 2;
	}
	if (editor->opt_menu.activ_h == 3 \
		|| editor->opt_menu.activ_h == 6)
	{
		editor->opt_menu.bord_color_h[3] = COLOR_PRESSED;
		editor->opt_menu.bord_color_h[6] = COLOR_PRESSED;
		editor->opt_menu.activ_h = 3;
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
	i = 0;/* 
	while (i < NBHEIGHTS)
	{
		editor->opt_menu.bord_color_h[i] = COLOR_NORMAL;
		if (is_mouse_collide(mouse_pos, editor->opt_menu.h_rect[i]))
			editor->opt_menu.activ_h = i;
		i++;
	} */
	editor->opt_menu.bord_color_h[editor->opt_menu.activ_h] = COLOR_PRESSED;
}

void change_size(t_editor *editor, t_sdlmain *sdlmain)
{
	if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect_floor[1]) && sdlmain->event.wheel.y > 0 && editor->opt_menu.height_floor > 12)
	{
		editor->opt_menu.height_floor--;
	}
	else if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect_floor[1]) && sdlmain->event.wheel.y < 0 && editor->opt_menu.height_floor < 50)
	{
		editor->opt_menu.height_floor++;
	}
	if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect_ceiling[1]) && sdlmain->event.wheel.y > 0 && editor->opt_menu.height_ceiling < 50)
	{
		editor->opt_menu.height_ceiling++;
	}
	else if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect_ceiling[1]) && sdlmain->event.wheel.y < 0 && editor->opt_menu.height_ceiling > 10)
	{
		editor->opt_menu.height_ceiling--;
	}
	set_height_test(editor);
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
		/*
		i = 0; 
		while (i < NBHEIGHTS)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect[i]) && i != editor->opt_menu.activ_h)
				editor->opt_menu.bord_color_h[i] = COLOR_HOVER;
			else if (!is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect[i]) && i != editor->opt_menu.activ_h)
				editor->opt_menu.bord_color_h[i] = COLOR_NORMAL;
			special_case_height(editor);
			i++;
		} */
	}
}

int	compare_walls(t_wall_node *current_wall, t_wall_node *wall)
{
	if (current_wall->start.x == wall->end.x && current_wall->start.y == wall->end.y && current_wall->end.x == wall->start.x && current_wall->end.y == wall->start.y)
	{
		return (1);
	}
	return (0);
}

t_sector_node	*find_wall_neighbor(t_wall_node *wall, t_sector_node *sector_list)
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

void	find_neighbors(t_doom *doom)
{
	t_sector_node	*current_sector;
	t_wall_node		*current_wall;
	current_sector = doom->map.sector_head;
	while (current_sector != NULL)
	{
		current_wall = current_sector->wall_head;
		while (current_wall != NULL)
		{
			current_wall->neighbor_sector = find_wall_neighbor(current_wall, doom->map.sector_head);
			current_wall = current_wall->next;
		}
		current_sector = current_sector->next;
	}
}

int	editor_events(t_doom *doom)
{
	t_editor	*editor;
	t_sdlmain	*sdlmain;
	t_wall_node	*previous;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	check_quit(&doom->sdlmain.event, &doom->state);
	if (sdlmain->event.type == SDL_KEYDOWN)
	{
		check_menu(&doom->sdlmain.event, &doom->state, \
					&doom->menu.previous_state, EDITOR_STATE);
		if (sdlmain->event.key.keysym.sym == SDLK_u)
		{
			previous = undo_wall(editor->edit_map.sector_head);
			if (previous != NULL) // condition has to be added so walls from sector before get removed, too
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
		if (sdlmain->event.key.keysym.sym == SDLK_t \
			&& sdlmain->event.key.repeat == 0)
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
		if (sdlmain->event.key.keysym.sym == SDLK_r)
		{
			editor->edit_map.sector_head = doom->map.sector_head;
			//free(doom->map.sector_head);
			//doom->map.sector_head = NULL;
			//doom->map.sector_head = editor->edit_map.sector_head;
		}
	}
	if (sdlmain->event.type == SDL_MOUSEBUTTONDOWN \
		|| sdlmain->event.type == SDL_MOUSEMOTION \
		|| sdlmain->event.type == SDL_MOUSEWHEEL)
	{
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT \
				&& sdlmain->mouse_pos.x <= NBPOINTSROW \
				&& sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
			event_editor_surf(sdlmain->mouse_pos, editor);
		if (sdlmain->event.button.button == SDL_BUTTON_RIGHT \
				&& sdlmain->mouse_pos.x <= NBPOINTSROW \
				&& sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
				{
					get_sector_by_pos(editor->current_sector, vec_to_vecdb(sdlmain->mouse_pos), 10);
					//printf("%p\n", get_sector_by_pos(editor->edit_map.sector_head, vec_to_vecdb(sdlmain->mouse_pos), 5));
					// select "set_height"
				}
		SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
		mouse_in_options(editor, sdlmain);
		if (sdlmain->event.type == SDL_MOUSEWHEEL)
			change_size(editor, sdlmain);
	}/* 
	if (sdlmain->event.type == SDL_MOUSEWHEEL || sdlmain->event.type == SDL_MOUSEMOTION)
		change_size(editor, sdlmain); */
	if (doom->state != EDITOR_STATE)
	{
		find_neighbors(doom);
		itt_sector_wall_heads(doom->map.sector_head, &set_wall_length);
		return (1);
	}
	return (0);
}