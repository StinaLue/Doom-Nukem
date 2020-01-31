/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:47:42 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/31 16:12:39 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
			if (current_wall->wall_type == 1)
				current_wall->neighbor_sector = find_wall_neighbor(current_wall, doom->map.sector_head);
			else
				current_wall->neighbor_sector = NULL;
			current_wall = current_wall->next;
		}
		current_sector = current_sector->next;
	}
}

int	editor_events(t_doom *doom)
{
	t_editor	*editor;
	t_sdlmain	*sdlmain;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	check_quit(&doom->sdlmain.event, &doom->state);
	if (sdlmain->event.type == SDL_KEYDOWN)
		event_keydown(editor, doom, sdlmain);
	if (sdlmain->event.type == SDL_MOUSEBUTTONDOWN \
		|| sdlmain->event.type == SDL_MOUSEMOTION \
		|| sdlmain->event.type == SDL_MOUSEWHEEL)
	{
		event_mouse(editor, sdlmain);
	}
	/* 
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
