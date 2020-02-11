/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:00:02 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 16:01:31 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	mouse_in_options(t_editor *editor, t_sdlmain *sdlmain, \
							t_options_menu *menu, Uint8 button)
{
	if (is_mouse_collide(sdlmain->mouse_pos, editor->options_rect))
	{
		mouse_collide2(sdlmain, editor, menu, button);
		mouse_collide1(sdlmain, editor, menu);
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
	tmp_mouse = multvec(tmp_mouse, SIZEMAP);
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

void	event_mouse(t_editor *editor, t_sdlmain *sdlmain)
{
	Uint8 button;

	button = sdlmain->event.button.button;
	editor->loading_success = 0;
	if (button == SDL_BUTTON_LEFT \
		&& sdlmain->mouse_pos.x <= NBPOINTSROW \
		&& sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
		create_walls_on_map(sdlmain->mouse_pos, editor, &editor->wall_tmp);
	if (button == SDL_BUTTON_RIGHT && sdlmain->mouse_pos.x <= NBPOINTSROW \
		&& sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
		mouse_click_right(editor, sdlmain);
	base_color_rect_options(&editor->opt_menu);
	SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
	mouse_in_options(editor, sdlmain, &editor->opt_menu, button);
}
