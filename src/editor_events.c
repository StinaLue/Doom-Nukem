/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:47:42 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/21 17:47:02 by sluetzen         ###   ########.fr       */
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
	}
}

int	start_wall_exists(t_wall_node *wall)
{
	if (wall->start.x > 0 && wall->start.y > 0)
		return (1);
	return (0);
}

void	event_editor_surf(t_sdlmain *sdlmain, t_editor *editor)
{
	if (start_wall_exists(&editor->wall_tmp) \
		&& !(sdlmain->mouse_pos.x == editor->wall_tmp.end.x \
		&& sdlmain->mouse_pos.y == editor->wall_tmp.end.y))
	{
		editor->wall_tmp.end.x = sdlmain->mouse_pos.x;
		editor->wall_tmp.end.y = sdlmain->mouse_pos.y;
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
			add_sector_node(&editor->edit_map.sector_head);
			set_vec_values(&sdlmain->mouse_pos, &editor->start_sector);
			//editor->start_sector.x = sdlmain->mouse_pos.x;
			//editor->start_sector.y = sdlmain->mouse_pos.y;
			editor->wall_tmp.start.x = sdlmain->mouse_pos.x; // set_vec_values can be used if wall_tmp.start is int
			editor->wall_tmp.start.y = sdlmain->mouse_pos.y;
			editor->wall_tmp.end.x = sdlmain->mouse_pos.x;
			editor->wall_tmp.end.y = sdlmain->mouse_pos.y;
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
	i = 0;
	while (i < NBHEIGHTS)
	{
		editor->opt_menu.bord_color_h[i] = COLOR_NORMAL;
		if (is_mouse_collide(mouse_pos, editor->opt_menu.h_rect[i]))
			editor->opt_menu.activ_h = i;
		i++;
	}
	editor->opt_menu.bord_color_h[editor->opt_menu.activ_h] = COLOR_PRESSED;
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
			special_case_height(editor);
		}
		while (i < NBTEXTURES)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.text_rect[i]) && i != editor->opt_menu.activ_tex)
				editor->opt_menu.bord_color_text[i] = COLOR_HOVER;
			else if (!is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.text_rect[i]) && i != editor->opt_menu.activ_tex)
				editor->opt_menu.bord_color_text[i] = COLOR_NORMAL;
			i++;
		}
		i = 0;
		while (i < NBHEIGHTS)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect[i]) && i != editor->opt_menu.activ_h)
				editor->opt_menu.bord_color_h[i] = COLOR_HOVER;
			else if (!is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.h_rect[i]) && i != editor->opt_menu.activ_h)
				editor->opt_menu.bord_color_h[i] = COLOR_NORMAL;
			special_case_height(editor);
			i++;
		}
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
	}
	if (sdlmain->event.type == SDL_MOUSEBUTTONDOWN \
		|| sdlmain->event.type == SDL_MOUSEMOTION)
	{
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT \
				&& sdlmain->mouse_pos.x <= NBPOINTSROW \
				&& sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
			event_editor_surf(sdlmain, editor);
		SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
		mouse_in_options(editor, sdlmain);
	}
	if (doom->state != EDITOR_STATE)
		return (1);
	return (0);
}